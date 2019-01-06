class Protocol
{
  constructor()
  {
    this.buffer_ = Buffer.from('')
  }

  read(buffer)
  {
    if(buffer) this.buffer_ = Buffer.concat([this.buffer_, buffer])

    console.log('r', this.buffer_)

    if(this.buffer_.length >= 23)
    {
      let address       = this.buffer_[1] << 8;
      address          += this.buffer_[0];

      let ackCode      = this.buffer_[3] << 8;
      ackCode         += this.buffer_[2]

      let functionCode = this.buffer_[4]

      let crc           = this.buffer_[6] << 8;
      crc              += this.buffer_[5];

      let data = []

      this.buffer_ = this.buffer_.slice(23)
  
      return { address, ackCode, functionCode, data, crc }
    }
    else return null
  }

  write(address, ack_code, function_code, data)
  {
    const buffer = Buffer.alloc(23);

    buffer.writeUInt16LE(address, 0)
    buffer.writeUInt16LE(ack_code, 2)
    buffer.writeUInt8(function_code, 4)

    for(let i = 7; i < 23; i++)
    {
      buffer[i] = data[i - 7];
    }
 
    buffer.writeUInt16LE(0, 5)

    console.log('w', buffer)

    return buffer
  }
}

///////////////////////////////////////////////////////////////////////////////

class Serial
{
  constructor(path, baudRate = 9600)
  {
    this.events_ = 
    {
      open:  () => {},
      data:  () => {},
      error: () => {}
    }

    this.serialPort_ = new SerialPort(path, 
    {
      baudRate
    })

    this.serialPort_.on('open',  (...args) => setTimeout(() => this.events_.open (...args), 3000))
    this.serialPort_.on('data',  (...args) => this.events_.data (...args))
    this.serialPort_.on('error', (...args) => this.events_.error(...args))
  }

  write(buffer, fnc)
  {
    this.serialPort_.write(buffer, fnc)
  }

  on(name, fnc) { this.events_[name] = fnc }
}

///////////////////////////////////////////////////////////////////////////////

class tcp
{
  
}

///////////////////////////////////////////////////////////////////////////////

class Channel
{
  constructor(name, transport, protocol)
  {
    this.events_ =
    {
      open:  () => {},
      msg:   () => {},
      error: () => {}
    }

    this.name       = name
    this.transport_ = transport
    this.protocol_  = protocol
    this.open_      = false

    this.transport_.on('open',  (...args) => this.open         (...args))
    this.transport_.on('data',  (...args) => this.read         (...args))
    this.transport_.on('error', (...args) => this.events_.error(...args))
  }

  open(...args)
  {
    this.open_ = true
    this.events_.open(...args)
  }

  read(buffer)
  {
    let msg = this.protocol_.read(buffer)
    while(msg)
    {
      this.events_.msg(msg)
      msg = this.protocol_.read()
    }
  }

  write(address, ack_code, function_code, data, fnc = () => {})
  {
    if(!this.open_) fnc(new Error('e_channel_not_open'))
    else 
    {
      const buffer = this.protocol_.write(address, ack_code, function_code, data)
      this.transport_.write(buffer, fnc)
    }
  }

  on(name, fnc) { this.events_[name] = fnc }
}

///////////////////////////////////////////////////////////////////////////////

class Comm
{
  constructor()
  {
    this.events_ = 
    {
      open:  () => {},
      msg:   () => {},
      error: () => {}
    }

    this.ack_code_ = 1
    this.handles_  = {}
    this.channels_ = []

    this.timeout_ = setInterval(() => this.timeoutHandles(), 1000)

    this.functionCodes =
    {
      ack:          1,
      set_script0:  2,
      set_address:  6,
      set_is_relay: 7
    }

    this.instructionCodes = 
    {
      set_led0_off:         1,
      set_led0_solid_white: 2,
  
      set_led1_off:         16,
      set_led1_solid_white: 17,
  
      wait_for_button0_down: 35,
      wait_for_button1_down: 36,
  
      wait_for_ack_with_1s_timeout: 37,
      wait_for_ack_with_5s_timeout: 38,
  
      wait_for_500ms: 39,
      wait_for_1s:    40,
  
      goto_start: 100
    }
  }

  make_handle(ack, fnc)
  {
    this.handles_[ack] = { fnc: fnc || (() => {}), time: Date.now() }
  }

  timeoutHandles()
  {
    const dead_handles = []
    const now = Date.now()

    for(const k in this.handles_)
    {
      if(now - this.handles_[k].time > 1000)
      {
        dead_handles.push(k)
      }
    }

    for(const k of dead_handles)
    {
      this.handles_[k].fnc(new Error('timed_out'))
      delete this.handles_[k]
    }
  }

  on_open(channel)
  {
    this.events_.open(null, channel)
  }

  on_msg(channel, msg)
  {
    if(msg.functionCode === this.functionCodes.ack)
    {
      if(msg.ackCode in this.handles_) this.handles_[msg.ackCode].fnc(msg)
      delete this.handles_[msg.ackCode]
    }
    else
    {
      this.events_.msg(msg, channel)
    }
  }

  on_error(channel, msg)
  {
    this.events_.error(msg, channel)
  }

  addSerialTransport(name, path, baudRate, fnc = () => {})
  {
    const c = new Channel(name, new Serial(path, baudRate), new Protocol())

    c.on('open',  (...args) => this.on_open (c, ...args))
    c.on('msg',   (...args) => this.on_msg  (c, ...args))
    c.on('error', (...args) => this.on_error(c, ...args))

    this.channels_.push(c)
  }

  write_(address, function_code, data, fnc = () => {})
  {
    const ack_code = this.ack_code_++

    this.channels_.forEach(c => c.write(address, ack_code, function_code, data, err =>
    {
      if(err) fnc(err)
      else    this.make_handle(ack_code, fnc)
    }))
  }

  ack(node, ackCode, fnc = () => {})
  {
    this.channels_.forEach(c => c.write(node, ackCode, this.functionCodes.ack, Buffer.from(''), err =>
    {
      fnc(err)
    }))
  }

  setNodeScript(node, scriptIdx, script, fnc)
  {
    const data = Buffer.from(script)
    this.write_(node, this.functionCodes.set_script0, data, fnc)
  }

  setNodeAddress(node, address, fnc)
  {
    const data = Buffer.alloc(2)
    data.writeUInt16BE(Number(address))
    this.write_(node, this.functionCodes.set_address, data, fnc)
  }

  setNodeAsRelay(node, isRelay, fnc)
  {
    const data = Buffer.alloc(1)
    data.writeUInt8(isRelay)
    this.write_(node, this.functionCodes.set_is_relay, data, fnc)
  }

  on(name, fnc) { this.events_[name] = fnc }
}

module.exports = Comm

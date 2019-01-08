<template>

<span>
  <section class="hero is-fullheight is-light">

    <navv/>

    <div class="columns">

      <div class="column is-half is-offset-one-quarter">
       
        <h3 class="subtitle" ><small style="padding-left: 12px;">My Devices:</small></h3>

        <template v-for="e in this.res" >
          <!-- -->
          <div :key="e.id">
            <div class="card">
              <div class="card-content" >
                  <div class="media" >
                    <div class="media-content" style="overflow: hidden">
                      <p class="title is-3" style="text-transform: capitalize;">{{e.name || 'Unamed Device'}}</p>
                    </div>
                  </div>
              </div>
            </div>
            <!-- -->
            <div class="card">
              <div class="card-content" >
                  <div class="media" >
                    <div class="media-content" style="overflow: hidden">
                      <inputt label="🆔 Device ID"
                              placeholder="e.g. Porch Door Sensor"
                              :value="e.name" 
                              :working="handles[e.id + '_name'].timeout" 
                              :success="handles[e.id + '_name'].success"
                              :error="handles[e.id + '_name'].error"
                              v-on:change="val => on_device_property_change(e.id, 'name', val)"/>
                      <p class="subtitle is-6">Your device will be called by this name in updates and stuff.</moment></p>
                    </div>
                  </div>
              </div>
            </div>
            <!-- -->
            <div class="card">
              <div class="card-content" >
                  <div class="media" >
                    <div class="media-content" style="overflow: hidden">
                      <inputt label="✉️ Email Updates"
                              placeholder="e.g. youremail@email.com"
                              :value="e.email" 
                              :working="handles[e.id + '_email'].timeout" 
                              :success="handles[e.id + '_email'].success"
                              :error="handles[e.id + '_email'].error"
                              v-on:change="val => on_device_property_change(e.id, 'email', val)"/>
                      <p class="subtitle is-6">Your device will email updates to this address.</moment></p>                      
                    </div>
                  </div>
              </div>
            </div>
            <!-- -->
            <div class="card">
              <div class="card-content" >
                  <div class="media" >
                    <div class="media-content" style="overflow: hidden">
                      <inputt label="📉 Google Sheets"
                              placeholder="e.g. youremail@gmail.com"
                              :value="e.sheetsEmail" 
                              :working="handles[e.id + '_sheetsEmail'].timeout" 
                              :success="handles[e.id + '_sheetsEmail'].success"
                              v-on:change="val => on_device_property_change(e.id, 'sheetsEmail', val)"/>
                      <p class="subtitle is-6">Your device will feed data into a sheet on your Google Drive.</moment></p>
                      <p v-if="e.sheetsId" class="subtitle is-6"><a class="has-text-link" :href="link(e.sheetsId)">Open in Google Sheets</a></p>           
                    </div>
                  </div>
              </div>
            </div>
            <!-- -->
            <div class="card">
              <div class="card-content" >
                  <div class="media" >
                    <div class="media-content" style="overflow: hidden">
                      <a class="button is-danger" v-on:click="on_delete_device(e.id)">Forget this Device</a>
                    </div>
                  </div>
              </div>
            </div>
            <!-- -->
            <div style="padding: 10px"></div>
          </div>
  
        </template>

      </div>
    </div>
   
  </section>
  <footerr/>
</span>

</template>

<script>
import Navv  from './Navv'
import Footerr from './Footerr'
import Moment  from './Moment'
import Inputt  from './Inputt'
import cfg from '@/utils/cfg'
import session from '@/utils/session'
import api from '@/utils/api'

function on_device_property_change(id, property, value)
{
  this.$set(this.handles[id + '_' + property], 'success', null)
  this.$set(this.handles[id + '_' + property], 'error',   null)

  clearTimeout(this.handles[id + '_' + property].timeout)
  this.handles[id + '_' + property].timeout = setTimeout(() =>
  {
    api.set_device({ id, [property]: value }, (err, res) =>
    {
      if(err) this.$set(this.handles[id + '_' + property], 'error', 'Ooops, something went wrong.')
      else
      {
        this.res.find(r => r.id == id)[property] = value
        this.$set(this.handles[id + '_' + property], 'success', 'Device setting changed OK.')
      }
   
      this.handles[id + '_' + property].timeout = null
    })
  }, 500)
}

function on_delete_device(id)
{
  if(!confirm('Are you sure you want to forget this device?')) return

  api.delete_device({ id }, err =>
  {
    if(err) alert(err)
    else    this.res.splice(this.res.find(r => r.id == id), 1)
  })
}

function created()
{
  api.get_devices({}, (err, res) =>
  {
    for(let k of res)
    {
      this.$set(this.handles, k.id + '_name',        { success: null, error: null, timeout: null })
      this.$set(this.handles, k.id + '_email',       { success: null, error: null, timeout: null })
      this.$set(this.handles, k.id + '_sheetsEmail', { success: null, error: null, timeout: null })
    }
    this.res = res
  })
}

function link(sheetId)
{
  return `https://docs.google.com/spreadsheets/d/${sheetId}`
}

export default 
{
  name: 'devices',
  data () 
  {
    return {
      session,
      req: null,
      res: [],
      err: null,
      is_busy: false,
      handles: {}
    }
  },
  created: created,
  methods: { on_device_property_change, on_delete_device, link },
  components: { Navv, Footerr, Inputt }
}
</script>

<style scoped>

.hero 
{
   justify-content: initial;
}

</style>

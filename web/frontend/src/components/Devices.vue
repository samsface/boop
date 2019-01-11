<template>

<span>
  <section class="hero is-fullheight is-light">

    <navv/>

    <div class="columns">

      <div class="column is-half-desktop is-offset-one-quarter-desktop">
       
      

        <!-- no devices -->
        <div class="hero-body" v-if="res.length === 0 && !working">
          <div class="container has-text-centered" style="transform: translate(0, -35px)">
            <h1 class="title is-1">
              🤔 No devices yet...
            </h1>
            <h2 class="subtitle">
              Have you tried turning them off and on again?
            </h2>
          </div>
        </div>
        <!-- /no devices -->
        
        <device 
          v-for="r in this.res"
          :key="r.id"
          :res="r"
          :on_property_change="on_property_change"
          :on_delete_device="on_delete_device"/>

      </div>
    </div>
   
  </section>
  <footerr/>
</span>

</template>

<script>
import Navv  from './Navv'
import Footerr from './Footerr'
import Device from  './Device'
import cfg from '@/utils/cfg'
import session from '@/utils/session'
import api from '@/utils/api'

function created()
{
  this.working = true

  api.get_devices({}, (err, res) =>
  {
    this.working = false
    this.res     = res
  })
}

function on_property_change(id, property, value, fnc)
{
  api.set_device({ id, [property]: value }, (err, res) =>
  {
    if(err) fnc(err.message)
    else
    {
      console.log(res)
      this.$set(this.res, this.res.findIndex(r => r.id == id), res)
      fnc(null, 'Saved ok :)')
    }
  })
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

export default 
{
  name: 'devices',
  data () 
  {
    return {
      res:     [],
      err:     null,
      working: false
    }
  },
  created: created,
  methods: { on_property_change, on_delete_device },
  components: { Navv, Footerr, Device }
}
</script>

<style scoped>

.hero 
{
   justify-content: initial;
}

</style>

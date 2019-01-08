<template>

<span>
  <notifications v-bind:req="req"></notifications>
  <section class="hero is-fullheight is-light">
    <navv/>
    <loading v-if="is_busy"></loading>

    <div class="columns">

      <div class="column is-half is-offset-one-quarter">
       
        <h3 class="subtitle" style="padding-left:1.5rem;"><small>My Booprs</small></h3>

        <template v-for="e in this.res" >
          <div :key="e.id">
            <div class="card">
              <div class="card-content" >
                  <div class="media" >
                    <div class="media-left">
                      <figure class="image is-48x48" style="text-align: center">
                        <i class="fas fa-sss has-text-info" aria-hidden="true" style="font-size: 2.5rem"></i>
                      </figure>
                    </div>
                    <div class="media-content" style="overflow: hidden">
                      <p class="title is-1" style="text-transform: capitalize;">{{e.name}}</p>
                    </div>
                  </div>
              </div>
            </div>
            <!-- -->
            <!-- -->
            <div class="card">
              <div class="card-content" >
                  <div class="media" >
                    <div class="media-left">
                      <figure class="image is-48x48" style="text-align: center;">
                        <i class="fas has-text-info" aria-hidden="true" style="font-size: 2.5rem;">🆔</i>
                      </figure>
                    </div>
                    <div class="media-content" style="overflow: hidden">
                      <p class="title is-4">Device Name:</p>
                      <inputt placeholder="e.g. Porch Door Sensor"
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
                    <div class="media-left">
                      <figure class="image is-48x48" style="text-align: center;">
                        <i class="fas has-text-info" aria-hidden="true" style="font-size: 2.5rem;">✉️</i>
                      </figure>
                    </div>
                    <div class="media-content" style="overflow: hidden">
                      <p class="title is-4">Email Updates:</p>
                      <inputt placeholder="e.g. youremail@gmail.com"
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
                    <div class="media-left">
                      <figure class="image is-48x48" style="text-align: center;">
                        <i class="fab has-text-info" aria-hidden="true" style="font-size: 2.5rem;">📉</i>
                      </figure>
                    </div>
                    <div class="media-content" style="overflow: hidden">
                      <p class="title is-4">Google Sheets:</p>
                      <inputt placeholder="e.g. youremail@gmail.com"
                              :value="e.sheetsEmail" 
                              :working="handles[e.id + '_sheetsEmail'].timeout" 
                              :success="handles[e.id + '_sheetsEmail'].success"
                              v-on:change="val => on_device_property_change(e.id, 'sheetsEmail', val)"/>
                      <p class="subtitle is-6">Your device will feed data into a sheet on your Google Drive.</moment></p>
                      <p v-if="e.sheetsId" class="subtitle is-6"><a class="has-text-link" :href="link(e.sheetsId)">Goto Google Sheets</a></p>           
                    </div>
                  </div>
              </div>
            </div>
            <!-- -->
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
        this.$set(this.handles[id + '_' + property], 'success', 'Device name changed OK.')
      }
   
      this.handles[id + '_' + property].timeout = null
    })
  }, 500)
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
  name: 'settings',
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
  methods: { on_device_property_change, link },
  components: { Navv, Footerr, Inputt }
}
</script>

<style scoped>
.search-form
{
  padding: 10px 24px 10px 24px;
}

.hero 
{
   justify-content: initial;
}

.tutorial
{
  max-width: 400px;
  margin: auto auto auto auto;
}

textarea
{
  border: none;
  color: rgba(54,54,54,.9);
  font-size: 1rem;
}

.tile.ancestor
{
  margin: 0px;
}

input
{
  font-weight: bold;
}

@media (max-width: 450px) 
{
  .columns
  {
    margin-left: 0px;
    margin-right: 0px;
  }

  .column
  {
    padding-left: 0px;
    padding-right: 0px;
  }

  .title.is-1
  {
    font-size: 2.5rem;
  }
} 

</style>

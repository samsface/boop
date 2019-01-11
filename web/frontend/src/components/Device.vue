<template>
<div>
    <!-- title -->
    <div class="card">
        <div class="card-content" >
            <div class="media" >
            <div class="media-content" style="overflow: hidden">
                <p class="title is-3" style="text-transform: capitalize;">{{res.name || 'Unamed Device'}}</p>
                <p class="sub-title is-3" style="text-transform: capitalize;">#{{res.id}}</p>
            </div>
            </div>
        </div>
    </div>
    <!-- /title -->
    <!-- name -->
    <div class="card">
      <div class="card-content">
        <div class="media">
          <div class="media-content" style="overflow: hidden">
            <inputt label="🆔 Device ID"
                    placeholder="e.g. Porch Door Sensor"
                    :value="res.name"
                    v-on:submit="(val, fnc) => on_property_change(res.id, 'name', val, fnc)"/>
            <p class="subtitle is-6">Your device will be called by this name in updates and stuff.</p>
          </div>
        </div>
      </div>
    </div>
    <!-- /name -->
    <!-- script -->
    <div class="card">
      <div class="card-content" >
        <div class="media" >
          <div class="media-content" style="overflow: hidden">
            <scriptt 
              :res="res.script"
              @submit="(val, fnc) => on_property_change(res.id, 'script', val, fnc)"/>
            <p class="subtitle is-6">Your device will execute this script from left to right, line by line.</moment></p>
          </div>
        </div>
      </div>
    </div>
    <!-- script -->
    <!-- email -->
    <div class="card">
      <div class="card-content" >
        <div class="media" >
          <div class="media-content" style="overflow: hidden">
            <inputt label="✉️ Email Updates"
                    placeholder="e.g. youremail@email.com"
                    :value="res.email" 
                    v-on:submit="(val, fnc) => on_property_change(res.id, 'email', val, fnc)"/>
            <p class="subtitle is-6">Your device will email updates to this address.</p>                      
          </div>
        </div>
      </div>
    </div>
    <!-- /email -->
    <!-- sheets -->
    <div class="card">
      <div class="card-content" >
        <div class="media" >
          <div class="media-content" style="overflow: hidden">
            <inputt label="📉 Google Sheets"
                    placeholder="e.g. youremail@gmail.com"
                    :value="res.sheetsEmail" 
                    v-on:submit="(val, fnc) => on_property_change(res.id, 'sheetsEmail', val, fnc)"/>
            <p class="subtitle is-6">Your device will feed data into a sheet on your Google Drive.</moment></p>
            <p v-if="res.sheetsId" class="subtitle is-6"><a class="has-text-link" :href="link(res.sheetsId)">Open in Google Sheets</a></p>           
          </div>
        </div>
      </div>
    </div>
    <!-- /sheets -->
    <!-- delete -->
    <div class="card">
      <div class="card-content" >
        <div class="media" >
          <div class="media-content" style="overflow: hidden">
            <button class="button is-danger" v-on:click="on_delete_device(res.id)">Forget this Device</button>
          </div>
        </div>
      </div>
    </div>
    <!-- /delete -->
   
</div>
</template>

<script>
import Inputt  from './Inputt'
import Scriptt  from './Scriptt'

function link(sheetId)
{
  return `https://docs.google.com/spreadsheets/d/${sheetId}`
}

export default 
{
  name: 'device',
  props: ['res', 'on_property_change', 'on_delete_device'],
  data () 
  {
    return {
    }
  },
  methods: { link },
  components: { Inputt, Scriptt }
}
</script>

<style scoped>
</style>

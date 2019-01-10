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
    <!--
    <div class="card">
        <div class="card-content" >
            <div class="media" >
            <div class="media-content" style="overflow: hidden">
                
                <div class="field">
                <label class="label">⚙️ Program</label>

                <div class="columns is-multiline">
                    
                    <div class="column is-one-quarter-desktop is-half-tablet" v-for="i in res.script">

                    <div class="select is-fullwidth" >
                        <select>
                        <option>Set LED Off</option>
                        <option>Set LED On</option>
                        <option>Wait for Button</option>
                        <option>Wait for 500ms</option>
                        <option>Wait for 1 sec</option>
                        <option value=100>Goto Start</option>
                        </select>
                    </div>

                    </div>

                </div>

                </div>
            
                <p class="subtitle is-6">Your device will execute these instructions.</moment></p>
            </div>
            </div>
        </div>
    </div>
    -->
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
  components: { Inputt }
}
</script>

<style scoped>
</style>

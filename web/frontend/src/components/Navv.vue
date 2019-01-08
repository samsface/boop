<template>
   <div class="hero-head">
      <nav class="navbar">
         <div class="container">
            <div class="navbar-brand">
               <router-link to="/" class="navbar-item"><strong>Boopr</strong></router-link>
               <div class="navbar-burger burger" v-on:click="is_active=!is_active" v-bind:class="{ 'is-active': is_active }">
                  <span></span>
                  <span></span>
                  <span></span>
               </div>
            </div>
            <div class="navbar-end navbar-menu" v-bind:class="{ 'is-active': is_active }">

              <div class="navbar-item">
                <div class="field is-grouped">

                 <p class="control">
                    <router-link :to="{ name: 'Devices' }" class="button is-link">
                      <span class="icon">
                        <i class="fa">🤖</i>
                      </span>
                      <span>My Devices</span>
                    </router-link>
                  </p>                         
                </div>
              </div>
            </div>
         </div>
      </nav>
   </div>
</template>

<script>
import session from "@/utils/session"
import cfg from "@/utils/cfg"

function on_copy_greeting()
{
  this.greeting_just_copied = true
  setTimeout(e => this.greeting_just_copied = false, 2000)
}

export default 
{
  name: 'navv',
  props: ['req'],
  data () 
  {
    return {
      session,
      cfg,
      is_active: false,
      greeting_just_copied: false
    }
  },
  computed: { greeting: function(){ return 'xxx' } }, 
  methods: { on_copy_greeting }
}
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
</style>
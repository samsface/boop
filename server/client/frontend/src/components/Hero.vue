<template>
   <span>

      <section class="hero is-fullheight is-light">

         <navv/>

         <div class="hero-body">

            <div class="container has-text-centered" style="transform: translate(0, -35px)">
               <span class="bunnies">🤖💬</span>
               <h1 class="title is-1">
                  Easy WiFi Buttons
               </h1>
               <h2 class="subtitle fade-out-start">
                  This is a stupud thing nobody reads.
               </h2>
               <search-form v-on:req="on_req"/>
            </div>

         </div>
      </section>

      <footerr></footerr>
   </span>
</template>

<script>
import Navv  from './Navv'
import Footerr from './Footerr'

function on_req(req)
{
   this.$router.push({ name: 'Search', query: Object.assign({}, this.$route.query, req) })
}

export default 
{
  name: 'hero',
  methods: { on_req },
  created: function(){ if(session.has_seen_hero) { this.on_req() } session.has_seen_hero = true;  },
  components: { Navv, Footerr }
}
</script>

<style scoped>
.bunnies
{
   color: #363636;
   font-size: 9rem;
}

.subtitle
{
  font-size: 1.52rem;
}

@media (max-width: 500px) 
{
  .bunnies
  {
    font-size: 8rem;;
  }
}

@media (max-width: 450px) 
{
  .bunnies
  {
    font-size: 2rem;;
  }

  .title
  {
    font-size: 2.59rem;;
  }

  .subtitle
  {
     font-size: 1.28rem;
  }
}
</style>

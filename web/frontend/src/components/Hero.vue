<template>
   <span>

      <section class="hero is-fullheight">

         <navv/>

         <div class="hero-body">

            <div class="container has-text-centered" style="transform: translate(0, -35px)">
               <span class="bunnies">🤖💬</span>
               <h1 class="title is-1">
                  Easy WiFi Buttons
               </h1>
               <h2 class="subtitle">
                  This is a stupud thing nobody reads.
               </h2>
            </div>

         </div>
      </section>

      <footerr></footerr>
   </span>
</template>

<script>
import Navv  from './Navv'
import Footerr from './Footerr'

export default 
{
  name: 'hero',
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

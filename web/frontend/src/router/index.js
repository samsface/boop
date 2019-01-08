import Vue     from 'vue'
import Router  from 'vue-router'
import Hero    from '@/components/Hero'
import Devices from '@/components/Devices'

Vue.use(Router)

export default new Router(
{
  mode: 'hash',
  routes: 
  [
    {
      path: '/',
      name: 'Hero',
      component: Hero
    },
    {
      path: '/devices',
      name: 'Devices',
      component: Devices
    }
  ]
})

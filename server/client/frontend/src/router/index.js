import Vue from 'vue'
import Router from 'vue-router'
import Hero from '@/components/Hero'
import Settings from '@/components/Settings'

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
      path: '/settings',
      name: 'Settings',
      component: Settings
    }
  ]
})

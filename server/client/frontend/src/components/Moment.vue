<template>
  <span>{{human_readable_date}}</span>
</template>
    
<script>
import moment from 'moment'

export default 
{
  name: 'moment',
  props: ['timestamp'],
  computed: { human_readable_date: function() { return moment(this.timestamp).startOf('second').fromNow() } }
}
</script>
 
 <!-- Add "scoped" attribute to limit CSS to this component only -->
 <style scoped>
 </style>
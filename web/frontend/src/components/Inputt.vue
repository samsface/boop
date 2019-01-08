<template>
<div class="field">
  <label class="label">{{label}}</label>
  <div class="control" v-bind:class="{ 'is-loading': working }">
    <input class="input"
           v-bind:class="{ 'is-danger' : error, 'is-success': success }"
           type="text" 
           :placeholder="placeholder" 
           v-model="v" 
           v-on:keyup="on_change"/>
  </div>
 <p class="help is-danger">{{error}}</p>
 <p class="help is-success">{{success}}</p>
</div>
</template>    
<script>

function on_change()
{
  this.v = this.v.trimLeft()
  if(this.v != this.o)
  {   
    this.o = '' + this.v
    this.$emit('change', this.v)
  }
}

export default 
{
  props: ['label', 'value', 'error', 'success', 'working', 'placeholder'],
  data () 
  {
    return {
      v: '' + this.value,
      o: '' + this.value
    }
  },
  methods: { on_change }
 }
 </script>
 
<style scoped>
</style>
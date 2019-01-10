<template>
  <form v-on:submit.prevent="on_submit">

    <label class="label">{{label}}</label>

    <!-- field -->
    <div class="field " v-bind:class="{ 'has-addons' : c }">

      <!-- input  -->
      <div class="control is-expanded" v-bind:class="{ 'is-loading': working }">

        <input class="input is-fullwidth"
              v-bind:class="{ 'is-danger' : error, 'is-success': success }"
              type="text" 
              :placeholder="placeholder" 
              :disabled="working"
              v-model="v" 
              v-on:keyup="on_change"/>
      </div>
      <!-- /input -->

      <!-- Save button -->
      <div v-if="c && !error" class="control">
        <input :disabled="working" type="submit" value="Save" class="button is-success"/>
      </div>
      <!-- /save button -->

      <!-- try again button -->
      <div v-if="c && error" class="control">
        <input :disabled="working" type="submit" value="Try Again" class="button is-danger"/>
      </div>
      <!-- /try again button -->

    </div>
    <!-- /field -->

    <!-- success & error messages -->
    <div  style="transform: translateY(-8px)">
      <p class="help is-danger">{{error}}</p>
      <p class="help is-success">{{success}}</p>
    </div>
    <!-- /success & error messages -->

  </form>
</template>    
<script>

function reset()
{
  this.error   = null
  this.success = null
  this.working = null
}

function on_change(evt)
{
  if(evt.keyCode === 13) return

  this.reset()

  this.v = this.v.trimLeft()
  if(this.v != this.o)
  {   
    this.o = '' + this.v
    this.$emit('change', this.v)

    this.c = true
  }
}

function on_submit()
{
  if(!this.c) return

  this.reset()
  this.working = true

  this.$emit('submit', this.v, (error, success) =>
  {
    this.working = false

    if(error) this.error   = error
    else
    {
      this.c       = false
      this.success = success
    }
  })
}

export default 
{
  props: ['label', 'value', 'placeholder'],
  data () 
  {
    return {
      error:   null,
      success: null,
      working: null, 
      v: '' + this.value,
      o: '' + this.value,
      c: false
    }
  },
  methods: { reset, on_change, on_submit }
 }
 </script>
 
<style scoped>
</style>
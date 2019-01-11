<template>
  <form v-on:submit.prevent="on_submit">
    <div class="field">
      <label class="label">📜 Script</label>
      <div class="columns is-multiline">
        <div v-for="r, i in res_" v-if="res_[i-1] != 100" class="column is-one-quarter-desktop is-half-tablet">
          <div class="select is-fullwidth"> 
            <select v-model="res_[i]" @change="on_change" :disabled="working">
                <option value=1>🚨 Set LED Off</option>
                <option value=2>🚨 Set LED On</option>
                <option value=3>🛎️ Wait for Button</option>
                <option value=4>⌛ Wait for 500 ms</option>
                <option value=5>⌛ Wait for 1 sec</option>
                <option value=6>💤 Sleep for 1 min</option>
                <option value=7>💤 Sleep for 10 min</option>
                <option value=100>️↩️ Goto Start</option>
            </select>
          </div>
        </div>
      </div>
    </div>

    <!-- save button -->
    <div v-if="c && !error" class="control">
      <input :disabled="working" type="submit" value="Save" class="button is-success"/>
    </div>
    <!-- /save button -->

    <!-- try again button -->
    <div v-if="c && error" class="control">
      <input :disabled="working" type="submit" value="Try Again" class="button is-danger"/>
    </div>
    <!-- /try again button -->

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
  this.c = true
}

function on_submit()
{
  if(!this.c) return

  this.reset()
  this.working = true

  this.$emit('submit', this.res_, (error, success) =>
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
  name: 'scriptt',
  props: ['res'],
  data () 
  {
    return {
      res_: this.res,
      error:   null,
      success: null,
      working: null, 
      c:    false
    }
  },
  methods: { reset, on_change, on_submit }
 }
 </script>
 
<style scoped>
</style>
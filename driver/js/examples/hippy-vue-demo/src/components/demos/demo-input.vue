<template>
  <div
    ref="inputDemo"
    class="demo-input"
    @click="blurAllInput"
  >
    <label>文本:</label>
    <input
      ref="input"
      v-model="text"
      placeholder="Text"
      caret-color="yellow"
      caret-size="5"
      underline-color-android="grey"
      placeholder-text-color="#40b883"
      :editable="true"
      class="input"
      @click="stopPropagation"
      @keyboardWillShow="onKeyboardWillShow"
      @keyboardWillHide="onKeyboardWillHide"
      @blur="onBlur"
      @focus="onFocus"
    >
    <div>
      <span>文本内容为：</span>
      <span>{{ text }}</span>
    </div>
    <div><span>{{ `事件: ${event} | isFocused: ${isFocused}` }}</span></div>
    <button
      class="input-button"
      @click="clearTextContent"
    >
      <span>清空文本内容</span>
    </button>
    <button
      class="input-button"
      @click="focus"
    >
      <span>Focus</span>
    </button>
    <button
      class="input-button"
      @click="blur"
    >
      <span>Blur</span>
    </button>
    <label>数字:</label>
    <input
      type="number"
      caret-color="yellow"
      caret-size="5"
      underline-color-android="grey"
      placeholder-text-color="#40b883"
      placeholder="Number"
      class="input"
      @change="textChange"
      @click="stopPropagation"
    >
    <label>密码:</label>
    <input
      type="password"
      caret-color="yellow"
      caret-size="5"
      underline-color-android="grey"
      placeholder-text-color="#40b883"
      placeholder="Password"
      class="input"
      @change="textChange"
      @click="stopPropagation"
    >
    <label>文本（限制5个字符）:</label>
    <input
      :maxlength="5"
      caret-color="yellow"
      caret-size="5"
      underline-color-android="grey"
      placeholder-text-color="#40b883"
      placeholder="5 个字符"
      class="input"
      @change="textChange"
      @click="stopPropagation"
    >
  </div>
</template>

<script>
import Vue from 'vue';

export default {
  /**
   * 组件加载时自动 focus 第一个输入框
   */
  data() {
    return {
      text: '',
      event: undefined,
      isFocused: undefined,
    };
  },
  mounted() {
    this.getChildNodes(this.$refs.inputDemo.childNodes).find(element => element.tagName === 'input')
      .focus();
  },
  methods: {
    /**
     * 当文字改变时输出
     */
    textChange(evt) {
      console.log(evt.value);
    },
    /**
     * 当点击顶部 View 时取消所有输入框的 focus 状态
     */
    blurAllInput() {
      this.getChildNodes(this.$refs.inputDemo.childNodes).filter(element => element.tagName === 'input')
        .forEach(input => input.blur());
    },
    /**
     * 点击输入框时，点击事件会冒泡到顶部 View 导致 focus 时又被 blur 了，所以这里需要阻止一下冒泡
     */
    stopPropagation(evt) {
      evt.stopPropagation();
    },
    clearTextContent() {
      this.text = '';
    },
    onKeyboardWillHide() {
      console.log('onKeyboardWillHide');
    },
    onKeyboardWillShow(evt) {
      console.log('onKeyboardWillShow', evt);
    },
    getChildNodes(childNodes) {
      return !Vue.Native ? Array.from(childNodes) : childNodes;
    },
    focus(evt) {
      evt.stopPropagation();
      this.$refs.input.focus();
    },
    blur(evt) {
      evt.stopPropagation();
      this.$refs.input.blur();
    },
    async onFocus() {
      this.isFocused = await this.$refs.input.isFocused();
      this.event = 'onFocus';
    },
    async onBlur() {
      this.isFocused = await this.$refs.input.isFocused();
      this.event = 'onBlur';
    },
  },
};
</script>

<style scoped>
.demo-input {
  display: flex;
  flex: 1;
  align-items: center;
  flex-direction: column;
  margin: 7px;
}
.demo-input .input {
  width: 300px;
  height: 48px;
  color: #242424;
  border-width: 1px;
  border-style: solid;
  border-color: #ccc;
  font-size: 16px;
  margin: 20px;
}
.demo-input .input-button {
  border-color: #4c9afa;
  border-width: 1px;
  border-style: solid;
  padding-left: 10px;
  padding-right: 10px;
  margin-top: 5px;
  margin-bottom: 5px;
}
</style>

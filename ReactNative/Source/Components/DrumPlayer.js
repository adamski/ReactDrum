import React, { Component, PropTypes } from 'react'
import { View, StyleSheet, NavigatorIOS, Text, Platform, requireNativeComponent } from 'react-native'

var styles = StyleSheet.create({
  container: {
    flex: 1,
    // borderTopColor: colours.mediumOutline,
    // borderTopWidth: 1,
    backgroundColor: '#000'
  }
});

import { NativeModules } from 'react-native'
// const ScaleController = NativeModules.ReactScaleController;

console.log("about to requireNativeComponent ReactJuceView")
const ReactJuceView = requireNativeComponent('ReactJuceView', JuceComponent, { 
  nativeOnly: {
    showModal: true
  }
})
console.log("done requireNativeComponent")

class JuceComponent extends React.Component {

  static propTypes = {
    ...View.propTypes,
    onPressModalButton: React.PropTypes.func, 
    dummy: PropTypes.string
  }

  constructor(props) {
    super(props);
  }

  showModal = (event: Event) => { 

    if (!this.props.onPressModalButton)
      return

    this.props.onPressModalButton(event.nativeEvent.showModal)
  }

  render() {
    return <ReactJuceView {...this.props} />
  }
}


class DrumPlayer extends Component {

  componentWillMount() {
    // ScaleController.updateScaleFromJSON (JSON.stringify (scaleStore.currentScale.scale))
  }

  showModal = () => {
    console.log("showModal from DrumPlayer")

    this.props.navigator.showModal({
      screen: "reactDrum.ModalScreen",
      title: "Modal Screen",
      style: {
        backgroundBlur: "none",
        backgroundColor: "#888888DD"
      },
      navigatorStyle: { navBarHidden: true, ...navigatorStyle }
    }) 
  }

  render() {
    return (
      <View style={styles.container}>
        <JuceComponent style={{flex: 1}} onPressModalButton={this.showModal} />
      </View>
    )
  }
}

module.exports = DrumPlayer


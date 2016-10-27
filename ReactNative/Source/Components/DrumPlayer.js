import React, { Component, PropTypes } from 'react'
import { 
  View, 
  Text, 
  StyleSheet, 
  NativeModules,
  DeviceEventEmitter,
  requireNativeComponent } from 'react-native'

var styles = StyleSheet.create({
  container: {
    flex: 1,
  }
});

// const ScaleController = NativeModules.ReactScaleController;

console.log("about to requireNativeComponent ReactJuceView")
const ReactJuceView = requireNativeComponent('ReactJuceView', JuceComponent, { 
  nativeOnly: {
    showModal: true,
    juceAppHasInitialised: true
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
    super(props)
    this.state = {
      juceAppHasInitialised: false
    }
  }

  // componentDidMount() {
  //   setTimeout(() => {
  //     this.setState({juceAppHasInitialised: true})
  //   }, 8000)
  // }


  componentWillMount() {
    DeviceEventEmitter.addListener('juceAppHasInitialised', (event: Event) => {
      console.log("componentDidMount: juceAppHasInitialised")
      this.setState({juceAppHasInitialised: true})
    })
  }

  showModal = (event: Event) => { 

    if (!this.props.onPressModalButton)
      return

    this.props.onPressModalButton(event.nativeEvent.showModal)
  }

  render() {
    // if (this.state.juceAppHasInitialised) {
      return <ReactJuceView {...this.props} />
    // } else {
    //   return <Text>Initialising...</Text>
    // }
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
        <Text>Some text</Text>
        <JuceComponent 
          style={{flex: 1}} 
          onPressModalButton={this.showModal}
        />
      </View>
    )
  }
}

module.exports = DrumPlayer


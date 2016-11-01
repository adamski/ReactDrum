import React, { Component, PropTypes } from 'react'
import { View, Text, StyleSheet, NativeModules, requireNativeComponent } from 'react-native'

var styles = StyleSheet.create({
  container: {
    flex: 1,
  }
});

// const ScaleController = NativeModules.ReactScaleController;

console.log("about to requireNativeComponent ReactJuceView")
const ReactJuceView = requireNativeComponent('ReactJuceView', JuceComponent, { 
  nativeOnly: {
    showModal: true
  }
})
console.log("done requireNativeComponent")

class JuceComponent extends React.Component {
  static navigatorButtons = {
    leftButtons: [{
      icon: require('../../../images/navicon_menu.png'),
      id: 'sideMenu'
    }],
    rightButtons: [
    {
      title: 'Edit',
      id: 'edit'
    },
    {
      icon: require('../../../images/navicon_add.png'),
      id: 'add'
    }
    ]
  };

  static navigatorStyle = {
    navBarBackgroundColor: '#4dbce9',
    navBarTextColor: '#ffff00',
    navBarSubtitleTextColor: '#ff0000',
    navBarButtonColor: '#ffffff',
    statusBarTextColorScheme: 'light',
    tabBarBackgroundColor: '#4dbce9',
    tabBarButtonColor: '#ffffff',
    tabBarSelectedButtonColor: '#ffff00'
  };

  static propTypes = {
    ...View.propTypes,
    onPressModalButton: React.PropTypes.func, 
    dummy: PropTypes.string
  }

  constructor(props) {
    super(props)
  }

  showModal = (event: Event) => { 

    if (!this.props.onPressModalButton)
      return

    this.props.onPressModalButton(event.nativeEvent.showModal)
  }

  render() {
    return <ReactJuceView {...this.props} key="ReactJuceView" ref="ReactJuceView"/>
  }
}


class DrumPlayer extends Component {
  constructor() {
    super()
    this.state = {
      sampleName: "Roll"
    }
  }

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
        <JuceComponent style={{flex: 1}} onPressModalButton={this.showModal} sampleName={this.state.sampleName} ref="JuceComp" key="JuceComponent"/>
      </View>
    )
  }
}

module.exports = DrumPlayer


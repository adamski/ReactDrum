import { observable } from 'mobx'

class ReactDrumStore {
  @observable currentSample = 'Roll'
}

export default new ReactDrumStore()

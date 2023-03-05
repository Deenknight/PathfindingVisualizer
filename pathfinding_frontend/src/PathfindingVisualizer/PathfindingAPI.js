class PathfindingAPI {

  constructor(serviceAddress) {
    this.serviceAddress = serviceAddress;
  }

  makeURL(algorithm, start, end, walls){
    const resource = algorithm + "/" + start + "/" + end + "/" + walls;

  }
  
  runMazeGenerator(algorithm, start, end, walls, handler){
    fetch(this.makeURL())
    .then(res => res.json())
    .then((response) => {
      handler(response["result"]);
    }, 
    (err) => {
      handler(err);
      console.log(err)
    }
    )
  }

}

export default PathfindingAPI;
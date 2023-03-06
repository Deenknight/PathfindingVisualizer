class PathfindingAPI {

  constructor(serviceAddress) {
    this.serviceAddress = serviceAddress;
  }

  makeURL(start, end, rows, columns){
    const resource = start + "/" + end + "/" + rows + "/" + columns;
    
    return new URL(resource, this.serviceAddress)

  }
  
  runMazeGenerator(start, end, rows, columns, handler){
    
    fetch(this.makeURL(start, end, rows, columns))
      .then(res => res.json())
      .then((response) => {
        handler(response["walls"]);
      }, 
      (err) => {
        handler(err);
        console.log(err)
      }
      );
  }

}

export default PathfindingAPI;
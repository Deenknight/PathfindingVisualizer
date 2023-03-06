import React from 'react';
import './App.css';
import PathfindingVisualizer from './PathfindingVisualizer/PathfindingVisualizer';
import PathfindingAPI from './PathfindingVisualizer/PathfindingAPI';

function App() {
  return (
    <div className="App">
      <PathfindingVisualizer pathfindingAPI = {new PathfindingAPI('http://127.0.0.1:8080')}></PathfindingVisualizer>
    </div>
  );
}

export default App;

import React from "react";
import { BrowserRouter, Link, Route, Routes } from "react-router-dom";
import NavBar from "./components/NavBar";
import Test from "./components/Test";

const App: React.FC = () => {
  return (
    <>
      <BrowserRouter>
        <NavBar>
          <li>
            <Link to="/">Home</Link>
          </li>
          <li>
            <Link to="/test">Test</Link>
          </li>
        </NavBar>

        <Routes>
          <Route path="/" element={<></>} />
          <Route path="/test" element={<Test />} />
        </Routes>
      </BrowserRouter>
    </>
  );
};

export default App;

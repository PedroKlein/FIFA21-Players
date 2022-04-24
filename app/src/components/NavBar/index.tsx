import React from "react";
import "./styles.scss";

const NavBar: React.FC = ({ children }) => {
  return (
    <nav className="nav-bar">
      <ul>{children}</ul>
    </nav>
  );
};

export default NavBar;

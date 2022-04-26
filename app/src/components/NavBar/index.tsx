import React from "react";
import { Container } from "./styles";

const NavBar: React.FC = ({ children }) => {
  return (
    <Container>
      <ul>{children}</ul>
    </Container>
  );
};

export default NavBar;

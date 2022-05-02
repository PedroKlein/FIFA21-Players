import React from "react";
import { Link, useLocation } from "react-router-dom";
import { IRoutes } from "../../@types/routes.types";
import { Container, Item } from "./styles";

interface IProps {
  routes: IRoutes[];
}
const NavBar: React.FC<IProps> = ({ routes }) => {
  const location = useLocation();
  return (
    <Container>
      <ul>
        {routes.map((route) => (
          <Item key={route.path} isActive={location.pathname == route.path}>
            <Link to={route.path}>{route.title}</Link>
          </Item>
        ))}
      </ul>
    </Container>
  );
};

export default NavBar;

import React from "react";

import { Container, Title } from "./styles";

interface IProps {
  title: string;
}
const WrapView: React.FC<IProps> = ({ title, children }) => {
  return (
    <Container>
      <Title>
        <h2>{title}</h2>
      </Title>
      <div id="content">{children}</div>
    </Container>
  );
};

export default WrapView;

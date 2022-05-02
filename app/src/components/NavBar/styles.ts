import styled from "styled-components";

export const Container = styled.nav`
  overflow: hidden;
  background-color: var(--dark);
  position: sticky;
  top: 0;
  z-index: 2;
  width: 100%;
  height: 50px;
  ul {
    text-align: center;
    padding: 15px;
  }
`;

interface IProps {
  isActive?: boolean;
}
export const Item = styled.li<IProps>`
  display: inline;
  font-size: 1.7rem;
  a {
    background-color: ${(props) =>
      props.isActive ? "var(--secondary)" : "transparent"};
    padding: 14px;
    border-radius: 10px;
    transition: 0.5s ease;
    &:hover {
      background-color: var(--primary);
    }
  }
`;

import styled from "styled-components";

export const Container = styled.nav`
  overflow: hidden;
  background-color: var(--secondary);
  position: sticky;
  top: 0;
  z-index: 2;
  width: 100%;
  height: 50px;
  ul {
    text-align: center;
    padding: 15px;
    li {
      display: inline;
      font-size: 17px;
      a {
        color: var(--light-white);
        padding: 14px;
        border-radius: 10px;
        &:hover {
          background-color: var(--dark-light);
        }
      }
    }
  }
`;

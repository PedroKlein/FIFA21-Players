import styled from "styled-components";

export const Container = styled.nav`
  overflow: hidden;
  background-color: #333;
  position: sticky;
  top: 0;
  z-index: 2 ;
  width: 100%;
  height: 50px;
  ul {
    text-align: center;
    padding: 15px;
    li {
      display: inline;
      font-size: 17px;
      a {
        color: #f2f2f2;
        padding: 14px;
        &:hover {
          background-color: #111;
        }
      }
    }
  }
`;

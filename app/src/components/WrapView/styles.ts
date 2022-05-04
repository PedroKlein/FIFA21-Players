import styled from "styled-components";

export const Title = styled.div`
  display: flex;
  justify-content: center;
  align-items: center;
  grid-area: title;
  h2 {
    font-size: 4rem;
  }
`;

export const Container = styled.div`
  width: 100%;
  height: 100%;

  display: grid;
  grid-template-columns: 1fr;
  grid-template-rows: 80px 1fr;
  grid-template-areas:
    "title"
    "content";

  #content {
    height: 100%;
    width: 100%;
    grid-area: content;
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
  }
`;

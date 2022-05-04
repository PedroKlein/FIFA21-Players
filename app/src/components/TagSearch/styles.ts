import styled from "styled-components";

export const Container = styled.div`
  width: 100%;
  display: flex;
  align-items: center;
  flex-direction: column;
`;

export const Bar = styled.div`
  position: relative;
  max-width: 310px;
  label {
    position: absolute;
    left: 15px;
    top: 3px;
    cursor: pointer;
  }
  button {
    position: absolute;
    right: 19px;
    top: 2px;
    cursor: pointer;
  }
  input {
    appearance: text;
    box-sizing: content-box;
    font-family: inherit;
    width: 220px;
    height: 15px;
    border: none;
    outline: none;
    margin-left: 10px;
    margin-right: 16px;
    background: var(--light-white);
    border: solid 1px var(--light);
    padding: 5px 30px 5px 32px;
    border-radius: 10em;
    transition: all 0.5s;
  }
`;

export const Tags = styled.div`
  height: 40px;
  display: flex;
  flex-direction: row;
  justify-content: center;
  margin-top: 8px;
  div {
    display: flex;
    align-items: center;
    padding: 8px;
    background: var(--dark);
    border-radius: 10px;
    margin-right: 8px;

    button {
      margin-left: 4px;
      cursor: pointer;
    }
  }
`;

import { createGlobalStyle } from "styled-components";
import { device } from "../@types/devices.types";

export default createGlobalStyle`
  * {
    margin: 0;
    padding: 0;
    box-sizing: border-box;
  }
  html {
    min-height: 100%;
    font-size: 62.5%;
    background: var(--dark-light);
    color: var(--light-white);
    @media ${device.mobileL} {
      font-size: 50%;
    }
  }
  main{
    width:100%;
    height: 100vh - 50px;
    display: flex;
    justify-content:center ;
    align-items: center;
    margin-top: 50px; ;
    padding: 2rem;
    /* max-width: 1400px; */
    margin: 0 auto;
    @media ${device.mobileL} {
      margin-bottom: 80px;
    }
  }
  body{
    font-size: 1.6rem;
    &::-webkit-scrollbar{
      width: 0.5rem;
    }
    &::-webkit-scrollbar-track{
      background: var(--light);
    }
    &::-webkit-scrollbar-thumb{
      background: var(--primary-dark);
      border-radius: 16px;
    }
  }
  p{
    color: var(--dark-light);
  }
  *, button, input {
    font-family: Roboto;
    border: 0;
    background: none;
    -webkit-tap-highlight-color: transparent;
    &:focus {
    outline: 0;
    outline: none;
    } 
    input, textarea {
      background: var(--light-white);
    }
    
  }
  ul {
    list-style: none;
  }
  a{
    color: var(--light-white);
    text-decoration: none;
  }
  :root {
    ${(props) => {
      const theme = props.theme;
      let append = "";
      Object.entries(theme).forEach(([prop, value]) => {
        append += `--${prop}: ${value};`;
      });
      return append;
    }}
  }
`;

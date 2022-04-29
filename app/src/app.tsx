import React from "react";
import { BrowserRouter, Link, Route, Routes } from "react-router-dom";
import { ThemeProvider } from "styled-components";
import NavBar from "./components/NavBar";
import GlobalStyles from "./styles/GlobalStyles";
import { ThemeName, themes, ThemeType } from "./styles/themes";
import Home from "./views/Home";
import PlayersSearch from "./views/PlayersSearch";
import TagsSearch from "./views/TagsSearch";

const App: React.FC = () => {
  const themeName: ThemeName = "main";
  const currentTheme: ThemeType = themes[themeName];

  return (
    <ThemeProvider theme={currentTheme}>
      <GlobalStyles />
      <BrowserRouter>
        <NavBar>
          <li>
            <Link to="/">Home</Link>
          </li>
          <li>
            <Link to="/players">Players Search</Link>
          </li>
          <li>
            <Link to="/tags">Tags Search</Link>
          </li>
        </NavBar>
        <main>
          <Routes>
            <Route path="/" element={<Home />} />
            <Route path="/players" element={<PlayersSearch />} />
            <Route path="/tags" element={<TagsSearch />} />
          </Routes>
        </main>
      </BrowserRouter>
    </ThemeProvider>
  );
};

export default App;

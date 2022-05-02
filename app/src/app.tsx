import React from "react";
import { BrowserRouter, Link, Route, Routes } from "react-router-dom";
import { ThemeProvider } from "styled-components";
import { IRoutes } from "./@types/routes.types";
import NavBar from "./components/NavBar";
import GlobalStyles from "./styles/GlobalStyles";
import { ThemeName, themes, ThemeType } from "./styles/themes";
import Home from "./views/Home";
import PlayersSearch from "./views/PlayersSearch";
import TagsSearch from "./views/TagsSearch";

const ROUTES: IRoutes[] = [
  {
    title: "Home",
    path: "/",
    component: <Home />,
  },
  {
    title: "Players Search",
    path: "/players",
    component: <PlayersSearch />,
  },
  {
    title: "Tags Search",
    path: "/tags",
    component: <TagsSearch />,
  },
];

const App: React.FC = () => {
  const themeName: ThemeName = "main";
  const currentTheme: ThemeType = themes[themeName];

  return (
    <ThemeProvider theme={currentTheme}>
      <GlobalStyles />
      <BrowserRouter>
        <NavBar routes={ROUTES} />
        <main>
          <Routes>
            {ROUTES.map((route) => (
              <Route path={route.path} element={route.component} />
            ))}
          </Routes>
        </main>
      </BrowserRouter>
    </ThemeProvider>
  );
};

export default App;

export const themes = {
  main: {
    primary: "#4158d0",
    "primary-light": "#FF1E27",
    "primary-dark": "#4158d0",
    secondary: "#7D7D7D",
    "secondary-light": "#9E9E9E",
    "secondary-dark": "#575757",
    light: "#f7f7f7",
    "light-white": "#FFFFFF",
    "light-dark": "#D9D9D9",
    success: "#218739",
    danger: "#dc3545",
    warning: "#ffc107",
    info: "#128091",
    dark: "#141414",
    "dark-light": "#2d2d2d",
  },
};

// #28a745
//#17a2b8

export type ThemeName = keyof typeof themes;
export type ThemeType = typeof themes.main;

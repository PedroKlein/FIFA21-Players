#include "ui.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400

struct BindingUI
{
  static JSValue GetMessage(JSObject &obj, const JSArgs &args);

  static void OnRequestSearch(const JSObject &obj, const JSArgs &args);
};

UI::UI(Database &db)
    : db(db)
{
  app_ = App::Create();

  ///
  /// Create a resizable window by passing by OR'ing our window flags with
  /// kWindowFlags_Resizable.
  ///
  window_ = Window::Create(app_->main_monitor(), WINDOW_WIDTH, WINDOW_HEIGHT,
                           false, kWindowFlags_Titled | kWindowFlags_Resizable | kWindowFlags_Maximizable);

  ///
  /// Tell our app to use 'window' as our main window.
  ///
  /// This call is required before creating any overlays or calling App::Run
  ///
  app_->set_window(*window_.get());

  ///
  /// Create our HTML overlay-- we don't care about its initial size and
  /// position because it'll be calculated when we call OnResize() below.
  ///
  overlay_ = Overlay::Create(*window_.get(), 1, 1, 0, 0);

  ///
  /// Force a call to OnResize to perform size/layout of our overlay.
  ///
  OnResize(window_->width(), window_->height());

  ///
  /// Load a page into our overlay's View
  ///
  overlay_->view()->LoadURL("file:///index.html");

  ///
  /// Register our UI instance as an AppListener so we can handle the
  /// App's OnUpdate event below.
  ///
  app_->set_listener(this);

  ///
  /// Register our UI instance as a WindowListener so we can handle the
  /// Window's OnResize event below.
  ///
  window_->set_listener(this);

  ///
  /// Register our UI instance as a LoadListener so we can handle the
  /// View's OnFinishLoading and OnDOMReady events below.
  ///
  overlay_->view()->set_load_listener(this);

  ///
  /// Register our UI instance as a ViewListener so we can handle the
  /// View's OnChangeCursor and OnChangeTitle events below.
  ///
  overlay_->view()->set_view_listener(this);
}

UI::~UI()
{
}

void UI::Run()
{
  app_->Run();
}

void UI::OnUpdate()
{
  ///
  /// This is called repeatedly from the application's update loop.
  ///
  /// You should update any app logic here.
  ///
}

void UI::OnClose()
{
}

void UI::OnResize(uint32_t width, uint32_t height)
{
  overlay_->Resize(width, height);
}

void UI::OnFinishLoading(ultralight::View *caller)
{
  ///
  /// This is called when a frame finishes loading on the page.
  ///
}

void UI::OnDOMReady(ultralight::View *caller)
{
  ///
  /// This is called when a frame's DOM has finished loading on the page.
  ///
  /// This is the best time to setup any JavaScript bindings.
  ///

  context_ = caller->js_context();
  SetJSContext(context_);

  JSObject global = JSGlobalObject();

  global["OnRequestPlayersSearch"] = BindJSCallbackWithRetval(&UI::OnRequestPlayersSearch);
  global["OnRequestTagsSearch"] = BindJSCallbackWithRetval(&UI::OnRequestTagsSearch);
}

void UI::OnChangeCursor(ultralight::View *caller,
                        Cursor cursor)
{
  ///
  /// This is called whenever the page requests to change the cursor.
  ///
  /// We update the main window's cursor here.
  ///
  window_->SetCursor(cursor);
}

void UI::OnChangeTitle(ultralight::View *caller,
                       const String &title)
{
  ///
  /// This is called whenever the page requests to change the title.
  ///
  /// We update the main window's title here.
  ///
  window_->SetTitle(title.utf8().data());
}

JSValue UI::OnRequestPlayersSearch(const JSObject &obj, const JSArgs &args)
{

  ultralight::String search = args[0];
  std::string cppString(search.utf8().data());
  auto playersSearch = db.playersSearch(cppString);
  JSArray res;
  res.set_context(context_);

  for (auto &&player : playersSearch)
  {
    res.push((JSValue)player.toJsObject(context_));
  }

  return res;
}

JSValue UI::OnRequestTagsSearch(const JSObject &obj, const JSArgs &args)
{

  JSArray tags = args[0];
  std::vector<std::string> tagsCPP;

  for (size_t i = 0; i < tags.length(); i++)
  {
    ultralight::String tag = tags[i];
    tagsCPP.push_back(std::string(tag.utf8().data()));
  }

  auto tagsSearch = db.tagsSearch(tagsCPP);
  JSArray res;
  res.set_context(context_);

  for (auto &&player : tagsSearch)
  {
    res.push((JSValue)player.toJsObject(context_));
  }

  return res;
}

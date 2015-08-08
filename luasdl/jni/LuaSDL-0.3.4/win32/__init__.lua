------------------------------------------------------------------------
--
-- luasdl.lua
-- Currently for testing purposes.
--
-- This file is part of LuaSDL.
--
-- PUBLIC DOMAIN. Author: Kein-Hong Man <khman@users.sf.net> 2007
--
------------------------------------------------------------------------

------------------------------------------------------------------------
-- NOTE: currently contains a lot of test code
-- TODO: * from list... ok, err =  xpcall(f2, debug.traceback)
--       * wrap caller and allow return to an SDL screen with messages
------------------------------------------------------------------------

-- local ref to SDL library
local SDL = SDL

-- mini LuaSDL libraries
local MiniFont_new = loadfile(SDL.LuaSDL_DirExe.."minifont.lua")
local MiniPath_new = loadfile(SDL.LuaSDL_DirExe.."minipath.lua")

-- arguments passed to script
local arg = {...}

-- test initialization of SDL
if SDL.SDL_Init(SDL.SDL_INIT_EVERYTHING) < 0 then
  error("Couldn't initialize SDL: "..SDL.SDL_GetError().."\n")
  os.exit(1)
end

SDL.SDL_WM_SetCaption(SDL.LuaSDL_Version, SDL.LuaSDL_Version)

------------------------------------------------------------------------

-- [[
-- startup
--
local option
local screen = SDL.SDL_SetVideoMode(640, 480, 32, 0)
if not screen then
  error("Couldn't set video mode: "..SDL.SDL_GetError().."\n")
else

  -- clear to grey
  do
    local info = SDL.SDL_GetVideoInfo()
    local rect = SDL.SDL_Rect_local()
    rect.x, rect.y = 0, 0
    rect.w, rect.h = info.current_w, info.current_h
    local grey = SDL.SDL_MapRGB(screen.format, 0x80, 0x80, 0x80)
    SDL.SDL_FillRect(screen, rect, grey)
  end
  -- update screen later...

  -- grab and format SDL version info
  local v = SDL.SDL_version_new()
  SDL.SDL_VERSION(v)
  local SDLver = v.major.."."..v.minor.."."..v.patch
  SDL.SDL_version_delete(v)

  -- simple minifont demo
  local MiniFont = MiniFont_new()
  MiniFont:SetSurface(screen)
  MiniFont:SetWindow(10, 10, 550, 440)
  MiniFont:Clear()
-- [=[
  MiniFont:Print(
    SDL.LuaSDL_Version, "\n\n\n",
    "Running on SDL version ", SDLver, "\n\n"
  )
--]=]

--[=[
  -- test arguments passed from executable
  MiniFont:Print(
    "Arguments passed from command-line:\n",
    "#arg = ", #arg, "\n"
  )
  for i = 1, #arg do
    MiniFont:Print("arg["..i.."] = ", arg[i], "\n")
  end
  MiniFont:Print("\n")
--]=]

  -- test missing script variable
  if SDL.LuaSDL_NotFound then
    MiniFont:Print(
      "Script specified on command line was not found!\n",
      "Argument: ", SDL.LuaSDL_NotFound, "\n\n"
    )
  end

  -- main demo description text
  MiniFont:Print(
[[

There is a demo game, Meteor Shower, which was written in
Lua 4 by Thatcher Ulrich for the original LuaSDL.

[1] play Meteor Shower      [a] keyboard demo
[2] audio demo              [b] timer demo
[3] mixer demo              [c] mouse demo
[4] image demo              [d] HTTP reflector
[5] font demo
[6] videoinfo demo
[7] directories demo
[8] memory testing
[9] demo template
[0] spray some pixels
Press [Escape] to exit...

]]
  )

  -- list of demos accessible from this script
  local demo_list = {
    [SDL.SDLK_1] = "meteor_shower/meteor_shower.lua",
    [SDL.SDLK_2] = "audio/audio_demo.lua",
    [SDL.SDLK_3] = "audio/mixer_demo.lua",
    [SDL.SDLK_4] = "image/image_demo.lua",
    [SDL.SDLK_5] = "font/font_demo.lua",
    [SDL.SDLK_6] = "misc/videoinfo.lua",
    [SDL.SDLK_7] = "misc/directories.lua",
    [SDL.SDLK_8] = "misc/memory_test.lua",
    [SDL.SDLK_9] = "misc/template.lua",
    [SDL.SDLK_a] = "misc/keyboard.lua",
    [SDL.SDLK_b] = "misc/timer.lua",
    [SDL.SDLK_c] = "misc/mouse.lua",
    [SDL.SDLK_d] = "net/http_reflector.lua",
  }

  -- test PutPixel
-- [=[
  local spray = function()
    -- draw some pixels
    if SDL.SDL_MUSTLOCK(screen) ~= 0 then
      if SDL.SDL_LockSurface(screen) < 0 then
        error("Can't lock screen: "..SDL.SDL_GetError().."\n")
      end
    end
    for i = 1, 1000 do
      local c = SDL.SDL_MapRGB(screen.format, math.random(0, 255),
                               math.random(0, 255), math.random(0, 255))
      local x = math.random(0, screen.w-1)
      local y = math.random(0, screen.h-1)
      SDL.SDL_PutPixel(screen, x, y, c)
    end
    if SDL.SDL_MUSTLOCK(screen) ~= 0 then
      SDL.SDL_UnlockSurface(screen)
    end
  end
--]=]

  -- display screen and event loop
  SDL.SDL_UpdateRect(screen, 0, 0, 0, 0)
  local event = SDL.SDL_Event_local()
  while true do
    while (SDL.SDL_PollEvent(event) == 0) do
      SDL.SDL_Delay(10)
    end
    local c = event.type
    if c == SDL.SDL_KEYDOWN then
      local key = event.key.keysym.sym
      if key == SDL.SDLK_ESCAPE then
        break
      elseif demo_list[key] then
        option = demo_list[key]
        break
      elseif key == SDL.SDLK_0 then
        spray()
        SDL.SDL_UpdateRect(screen, 0, 0, 0, 0)
      end
    elseif c == SDL.SDL_QUIT then
      break
    end--if c
  end--while

  -- timer test
-- [=[
  if c_handle then
    SDL.SDL_RemoveTimer(c_handle)
  end
--]=]

  -- handle loading and calling demo script
  local MiniPath = MiniPath_new()
  if option then
    local demo_path = "../demos/"..option
    demo, err = loadfile(MiniPath:SetApp(demo_path))
    if not demo then
      MiniFont:GotoXY(0, 20)
      MiniFont:Print(err)
      MiniFont:Print("\nPress any key to exit...")
      SDL.SDL_UpdateRect(screen, 0, 0, 0, 0)
      local event = SDL.SDL_Event_local()
      while true do
        while (SDL.SDL_PollEvent(event) == 0) do
          SDL.SDL_Delay(10)
        end
        local c = event.type
        if c == SDL.SDL_KEYDOWN then
          break
        elseif c == SDL.SDL_QUIT then
          break
        end
      end--while
    end
  end

end
--]]

------------------------------------------------------------------------

SDL.SDL_Quit()

if demo then demo(...) end -- run next script if there is one

-- end of default script

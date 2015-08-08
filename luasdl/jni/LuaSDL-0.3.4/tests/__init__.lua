-- dump these here for now...

------------------------------------------------------------------------

--[[
print("SDL.Bool test:")
print("SDL.Bool(0) = "..tostring(SDL.Bool(0)))
print("SDL.Bool(1) = "..tostring(SDL.Bool(1)))
print("SDL.Bool(999) = "..tostring(SDL.Bool(999)))
print()

print("SDL.And test:")
print()
print("SDL.Or test:")
print()
print("SDL.Xor test:")
print()

print("SDL.Not test:")
print("SDL.Not(0) = "..tostring(SDL.Not(0)))
print("SDL.Not(0xFFFFFFFF) = "..tostring(SDL.Not(0xFFFFFFFF)))
print()

print("SDL.LShift test:")
print()
print("SDL.RShift test:")
print()
print("SDL.SDL_RWFromFP test:")
print()
--]]

------------------------------------------------------------------------

  -- for testing of memory management
  local luamem = function() return collectgarbage("count") * 1024 end
--[=[
  -- test SDL_NewUserData
  collectgarbage("collect")
  MiniFont:Print("Begin: "..luamem().."\n")
  local x = SDL.NewUserData(16384)
  MiniFont:Print("Create: "..luamem().."\n")
  local y = x
  x = nil
  collectgarbage("collect")
  MiniFont:Print("Reassign: "..luamem().."\n")
  y = nil
  collectgarbage("collect")
  MiniFont:Print("Collect: "..luamem().."\n")
--]=]

--[=[
  -- test of wrappers for memory debugging
  local try_ref = {}
  local old_pf_n = SDL.SDL_PixelFormat_new
  SDL.SDL_PixelFormat_new = function()
    print("Wrapper New")
    local obj = old_pf_n()
    try_ref[obj] = true
    return obj
  end
  local old_pf_d = SDL.SDL_PixelFormat_delete
  SDL.SDL_PixelFormat_delete = function(obj)
    print("Wrapper Delete")
    if not try_ref[obj] then
      print("serious problem...")
    end
    old_pf_d(obj)
  end
--]=]

--[=[
  collectgarbage("collect")
  MiniFont:Print("Begin: "..luamem().."\n")
  local t = {}
  for i = 1, 10 do
    t[i] = SDL.SDL_Rect_local()
    --t[i] = SDL.SDL_PixelFormat_new()
  end
  collectgarbage("collect")
  MiniFont:Print("Created: "..luamem().."\n")
  for i = 1, 10 do
    --SDL.SDL_PixelFormat_delete(t[i])
    --tolua.takeownership(t[i])
  end
  --t = nil
  collectgarbage("collect")
  MiniFont:Print("Nil-ed: "..luamem().."\n")
  collectgarbage("collect")
  MiniFont:Print("Again: "..luamem().."\n")
  collectgarbage("collect")
  MiniFont:Print("Again: "..luamem().."\n")
--]=]



------------------------------------------------------------------------
--
-- minipath.lua
-- A factory for minipath, a simple path normalization library.
--
-- This file is part of LuaSDL.
--
-- PUBLIC DOMAIN. Author: Kein-Hong Man <khman@users.sf.net> 2007
--
------------------------------------------------------------------------
-- * requires strings set up by LuaSDL, the SDL.LuaSDL_Dir* items
-- * abspath needs to have a trailing path separator
-- * recognizes absolute paths in filespec
-- * removes "." and ".." and redundant path separators
------------------------------------------------------------------------

local string = string
local match = string.match

return {
  --------------------------------------------------------------------
  Root = function(self, abspath)
    local root = match(abspath, "^[/\\]+")
    if root then return SDL.LuaSDL_DirSep end
    root = match(abspath, "^(%a:)[/\\]+")
    if root then return root..SDL.LuaSDL_DirSep end
    return ""
  end,
  --------------------------------------------------------------------
  Normalize = function(self, abspath, filespec)
    local root = self:Root(abspath)
    local rfile = self:Root(filespec)
    if #rfile > 0 then          -- check if filespec is absolute
      abspath = rfile
      filespec = string.sub(filespec, #rfile + 1)
    end
    while true do               -- process each segment
      local seg, rest = match(filespec, "^([^/\\]+)[/\\]+(.*)$")
      if not seg then break end
      filespec = rest
      if seg == "." then
      elseif seg == ".." and #abspath > #root then
        seg = match(abspath, "([^/\\]+[/\\]+)$")
        abspath = string.sub(abspath, 1, -1-#seg)
      else
        abspath = abspath..seg..SDL.LuaSDL_DirSep
      end
    end
    return abspath, filespec, abspath..filespec
  end,
  --------------------------------------------------------------------
  SetApp = function(self, filepath)
    SDL.LuaSDL_DirApp, SDL.LuaSDL_AppName, filepath
      = self:Normalize(SDL.LuaSDL_DirApp, filepath)
    return filepath
  end,
  --------------------------------------------------------------------
  RelExe = function(self, filepath)
    local _, _, fullpath = self:Normalize(SDL.LuaSDL_DirExe, filepath)
    return fullpath
  end,
  --------------------------------------------------------------------
  RelApp = function(self, filepath)
    local _, _, fullpath = self:Normalize(SDL.LuaSDL_DirApp, filepath)
    return fullpath
  end,
  --------------------------------------------------------------------
}

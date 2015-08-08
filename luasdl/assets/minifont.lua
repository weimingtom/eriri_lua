------------------------------------------------------------------------
--
-- minifont.lua
-- A factory for minifont, a simple message display library.
--
-- This file is part of LuaSDL.
--
-- PUBLIC DOMAIN. Author: Kein-Hong Man <khman@users.sf.net> 2007
--
------------------------------------------------------------------------
-- * requires SDL_image, for the RLE-compressed 8-bit BMP font data
-- * the font BMP is embedded in LuaSDL
-- * has wrapping, but cannot scroll or handle overfull screens
-- * \n recognized, \r ignored, \t unhandled for now
-- * all non-printable characters uses the 127 glyph
-- * remember to update the surface after using Print()
------------------------------------------------------------------------

local dest
local fontdata = SDL.SDL_RWFromMem(SDL.LuaSDL_FontBasic, 6814)
local fontsurf = SDL.IMG_LoadBMP_RW(fontdata)
SDL.SDL_FreeRW(fontdata)

local pos = SDL.SDL_Rect_local()
local src = SDL.SDL_Rect_local()

return {
  --------------------------------------------------------------------
  WIDTH = 8, HEIGHT = 14, LEADING = 16,
  border = 4,
  --------------------------------------------------------------------
  SetSurface = function(self, dst)
    dest = dst
  end,
  --------------------------------------------------------------------
  SetWindow = function(self, x, y, w, h, border)
    self.border = border or self.border
    self.startx, self.starty = x, y
    self.posx, self.posy = 0, 0
    self.sizew, self.sizeh = w, h
    self.maxcol = math.floor((w - 2 * self.border) / self.WIDTH)
    self.maxlin = math.floor((h - 2 * self.border) / self.LEADING)
    src.y = 0
    src.w, src.h = self.WIDTH, self.HEIGHT
  end,
  --------------------------------------------------------------------
  Print = function(self, ...)
    local txt = table.concat({...})
    pos.w, pos.h = self.WIDTH, self.HEIGHT
    for i = 1, #txt do
      local c = string.byte(txt, i)
      if c < 32 then
        -- no wrapping, CR ignored
        if c == 10 then
          self.posx, self.posy = 0, self.posy + 1
        elseif c == 13 then
        else c = 127
        end
      elseif c > 127 then
        c = 127
      end
      if c >= 32 then
        if self.posx >= self.maxcol then
          self.posx, self.posy = 0, self.posy + 1
        end
        if self.posy < self.maxlin then
          src.x = (c - 32) * self.WIDTH
          pos.x = self.startx + self.posx * self.WIDTH + self.border
          pos.y = self.starty + self.posy * self.LEADING + self.border
          SDL.SDL_BlitSurface(fontsurf, src, dest, pos)
          self.posx = self.posx + 1
        end
      end
    end--for
  end,
  --------------------------------------------------------------------
  GotoXY = function(self, x, y)
    self.posx, self.posy = x, y
  end,
  --------------------------------------------------------------------
  Clear = function(self)
    pos.x, pos.y = self.startx, self.starty
    pos.w, pos.h = self.sizew, self.sizeh
    local black = SDL.SDL_MapRGB(dest.format, 0x00, 0x00, 0x00)
    SDL.SDL_FillRect(dest, pos, black)
    self.posx, self.posy = 0, 0
  end,
  --------------------------------------------------------------------
}

function love.conf (t)
	t.console = false
	t.externalstorage = true
	-- t.audio.mic = true
	-- t.audio.mixwithststem = true

	t.window.title = "2048 by thebadzhang"
	t.window.icon = "2048.png"
	t.window.height = 800
	t.window.width = 600
	t.window.fullscreen = true
	-- t.window.fullscreentype = "exclusive"
	-- t.window.fullscreentype = "desktop"
	t.window.vsync = 1
	t.window.msaa = 0
	t.window.highdpi = true
	t.window.usedpiscale = true
	t.window.x = nil
	t.window.y = nil
	-- t.window.console = true
	-- t.modules./
end



usr = {
	score = 0,
	status = true,
	touchFlag = true
}
map = {
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0}
}

testMode = false
graphMode = false
graphNum = 0

font = {
	[20] = love.graphics.newFont (20),
	[40] = love.graphics.newFont (40),
	[70] = love.graphics.newFont (70)
}

function love.load ()
	math.randomseed (os.time ())
	if math.random (2) == 1 then
		map [math.random (4)][math.random (4)] = 2
	else
		map [math.random (4)][math.random (4)] = 4
	end
	bg = love.graphics.newImage ("bg.jpg")
	-- love.graphics.scale (2)
	width, height = love.graphics.getWidth (), love.graphics.getHeight ()
	scaleNum = math.min (height/600, width/800)
	-- love.window.setPosition ((width-600*scaleNum)/2,0)
	-- love.graphics.origin 
end

function love.draw ()

	love.graphics.push ()
	love.graphics.scale (scaleNum)
	-- love.graphics.translate ((width-800*scaleNum)/2,0)
	-- love.graphics.translate (10,10)
	love.graphics.translate ((width/scaleNum-800)/2,(height/scaleNum-600)/2)
	-- love.graphics.scale (800/love.graphics.getWidth (), 600/love.graphics.getHeight ())
	-- love.graphics.scale (2)
	love.graphics.draw (bg, 0, 0, 0, 0.4, 0.45)

	love.graphics.line (600, 0, 600, 600)

	love.graphics.rectangle ("line", 100, 100, 400, 400)
	love.graphics.line (200, 100, 200, 500)
	love.graphics.line (300, 100, 300, 500)
	love.graphics.line (400, 100, 400, 500)
	love.graphics.line (100, 200, 500, 200)
	love.graphics.line (100, 300, 500, 300)
	love.graphics.line (100, 400, 500, 400)
	love.graphics.line (100, 500, 500, 500)
	
	if usr.status then
		love.graphics.setFont (font [20])
		love.graphics.print (string.format ("SCORE: %d", usr.score), 620, 200)
		love.graphics.setFont (font [40])
		for tk, tv in ipairs(map) do
			for k, v in ipairs (tv) do
				love.graphics.print (string.format ("%d", v), 100+100*(k-1), 120+100*(tk-1))
			end
		end
	else
		love.graphics.setFont (font [70])
		love.graphics.print (string.format ("Game Finished\nScore: %d", usr.score), 150, 100)
	end
	if testMode then
		if graphMode then
			-- for i = 1, 4, 1 do
			-- 	for j = 1, 4, 1 do
			-- 		love.graphics.draw ()
			-- 	end
			-- end
		else
			love.graphics.setFont (love.graphics.newFont (40))
			for i = 1, 4, 1 do
				for j = 1, 4, 1 do
					love.graphics.print (string.format("%d", v), 100+100*(j-1), 100+100*(i-1))
				end
			end
		end
	end
	love.graphics.pop()
end


function moveUP ()
	local k = 1
	while k > 0 do
		k = 0
		for i = 2, 4, 1 do
			for j = 1, 4, 1 do
				if map[i-1][j] == 0 and map [i][j] ~= 0 then
					map [i-1][j] = map [i][j]
					map [i][j] = 0
					k = k + 1
				elseif map [i-1][j] == map [i][j] then
					map [i-1][j] = map [i-1][j] + map [i][j]
					map [i][j] = 0
				end
			end
		end
	end
end

function moveDOWN ()
	local k = 1
	while k > 0 do
		k = 0
		for i = 3, 1, -1 do
			for j = 1, 4, 1 do
				if map[i+1][j] == 0 and map [i][j] ~= 0 then
					map [i+1][j] = map [i][j]
					map [i][j] = 0
					k = k + 1
				elseif map [i+1][j] == map [i][j] then
					map [i+1][j] = map [i+1][j] + map [i][j]
					map [i][j] = 0
				end
			end
		end
	end
end

function moveLEFT ()
	local k = 1
	while k > 0 do
		k = 0
		for i = 1, 4, 1 do
			for j = 2, 4, 1 do
				if map[i][j-1] == 0 and map [i][j] ~= 0 then
					map [i][j-1] = map [i][j]
					map [i][j] = 0
					k = k + 1
				elseif map [i][j-1] == map [i][j] then
					map [i][j-1] = map [i][j-1] + map [i][j]
					map [i][j] = 0
				end
			end
		end
	end
end

function moveRIGHT ()
	local k = 1
	while k > 0 do
		k = 0
		for i = 1, 4, 1 do
			for j = 3, 1, -1 do
				if map[i][j+1] == 0 and map [i][j] ~= 0 then
					map [i][j+1] = map [i][j]
					map [i][j] = 0
					k = k + 1
				elseif map [i][j+1] == map [i][j] then
					map [i][j+1] = map [i][j+1] + map [i][j]
					map [i][j] = 0
				end
			end
		end
	end
end

function newNumber (towardsX, towardsY)
	numberCounter = 0
	for tk, tv in ipairs(map) do
		for k, v in ipairs (tv) do
			if v ~= 0 then numberCounter = numberCounter + 1 end
		end
	end
	if numberCounter == 16 then
		usr.status = false
	else
		repeat
			newNumberX = math.random (4)
			newNumberY = math.random (4)
		until map [newNumberX][newNumberY] == 0 and (newNumberX+towardsX >= 1 and newNumberX+towardsX <= 4 and newNumberY+towardsY >= 1 and newNumberY+towardsY <= 4 and map [newNumberX+towardsX][newNumberY+towardsY] ~= 0 or (towardsX == 1 and newNumberX == 4) or (towardsX == -1 and newNumberX == 1) or (towardsY == 1 and newNumberY == 4) or (towardsY == -1 and newNumberY == 1))
		if math.random (2) == 1 then
			map [newNumberX][newNumberY] = 2
		else
			map [newNumberX][newNumberY] = 4
		end
	end
end

function love.keypressed (key, scancoe, isrepeat)
	if usr.status ~= true then return end
	local correctkey = false
	local towardsX, towardsY
	if love.keyboard.isDown ("up") or love.keyboard.isDown ("w") then
		towardsX = 0
		towardsY = -1
		correctkey = true
		moveUP ()
	elseif love.keyboard.isDown ("down") or love.keyboard.isDown ("s") then
		towardsX = 0
		towardsY = 1
		correctkey = true
		moveDOWN ()
	elseif love.keyboard.isDown ("left") or love.keyboard.isDown ("a") then
		towardsX = -1
		towardsY = 0
		correctkey = true
		moveLEFT ()
	elseif love.keyboard.isDown ("right") or love.keyboard.isDown ("d") then
		towardsX = 1
		towardsY = 0
		correctkey = true
		moveRIGHT ()
	elseif love.keyboard.isDown ("t") then
		testMode = true
	elseif love.keyboard.isDown ("1") then
		graphNum = 1
	elseif love.keyboard.isDown ("2") then
		graphNum = 2
	elseif love.keyboard.isDown ("3") then
		graphNum = 3
	elseif love.keyboard.isDown ("4") then
		graphNum = 4
	elseif love.keyboard.isDown ("5") then
		graphNum = 5
	elseif love.keyboard.isDown ("6") then
		graphNum = 6
	elseif love.keyboard.isDown ("7") then
		graphNum = 7
	elseif love.keyboard.isDown ("8") then
		graphNum = 8
	elseif love.keyboard.isDown ("9") then
		graphNum = 9
	elseif love.keyboard.isDown ("0") then
		graphNum = 0
	end
	-- setNewNumberflag = false
	if correctkey then
		newNumber (towardsX, towardsY)
	end
end
function love.touchreleased ()
	usr.touchFlag = true
end
function love.touchmoved (id, x, y, dx, dy, pressure)
	if usr.status ~= true then return end
	local towardsX, towardsY
	if usr.touchFlag then
		usr.touchFlag = false
		if dy < 0 and math.abs (dy) > math.abs (dx) then
			towardsX = 0
			towardsY = -1
			moveUP ()
		elseif dy > 0 and math.abs (dy) > math.abs (dx) then
			towardsX = 0
			towardsY = 1
			moveDOWN ()
		elseif dx < 0 and math.abs (dx) > math.abs (dy) then
			towardsX = -1
			towardsY = 0
			moveLEFT ()
		elseif dx > 0 and math.abs (dx) > math.abs (dy) then
			towardsX = 1
			towardsY = 0
			moveRIGHT ()
		end
		-- setNewNumberflag = false
		newNumber (towardsX, towardsY)
	end
end

function love.update ()
	usr.score = 0
	for tk, tv in ipairs(map) do
		for k, v in ipairs (tv) do
			usr.score = usr.score + v
		end
	end
	-- if usr.sta
end
mutationRate = 0.03
generations = 200
populationSize =  15-- need a decently sized population
problemSize = 500
crossoverRate = 0.97
tournamentSize =  math.floor(populationSize/4) -- this DOES still work when = 2
globalX = 0
elitismOffset = math.floor(populationSize * 0.2)
startTime = 0
xmarked = false

function printf(...)
	io.write(string.format(...))
end

function subrange(t, first, last)
	local sub = {}
	for i=first,last do
		sub[#sub+1] = t[i]
	end
	return sub
end

function aggregate()	-- TODO This currently takes the average from the whole population. Needs to take average of the fittest members
						-- of the population instead! Replace 'population' in this function with 'parentPop'

	-- for each char in an individual, count the number of 1s, 2s, 3s, and 4s, and whichever has most will be added
	local s = ""
	local ones = 0
	local twos = 0
	local threes = 0
	local fours = 0
	
	for i=1, problemSize do
		for j=1, populationSize do -- check each individual in the population and count actions
			
			-- if population[i] contains 1, increment ones
			if (population[j]:sub(i,i) == "1") then
				ones = ones + 1
			elseif (population[j]:sub(i,i) == "2") then
				twos = twos + 1
			elseif (population[j]:sub(i,i) == "3") then
				threes = threes + 1
			elseif (population[j]:sub(i,i) == "4") then
				fours = fours + 1
			else
				emu.message("Error: " .. j .. "th member of population contains " .. population[j]:sub(j,j))
			end
		end
		-- after checking this character for all individuals, find out which character occurs the most
		largest = ones
		c = "1"
		if twos > largest then 
			largest = twos
			c = "2"
		end
		if threes > largest then
			largest = threes
			c = "3"
		end
		if fours > largest then
			largest = fours
			c = "4"
		end
		-- add that character to the aggregate string
		s = s .. c
		ones = 0
		twos = 0
		threes = 0
		fours = 0
	end
	-- superIndividual will be the first member of the population because it's placed in the table first.
	return s
end

-- selects what individuals from the parent population will be parents together and breeds them
function reproduce(selected)
	local pop = {}
		
	for i, p1 in ipairs(selected) do
		-- if i = 2, 4, 6: use previous individual as p2.
		-- if i = 1,3, but not the last individual: use next individual as p2.
		-- if i = last individual, use previous individual as p2.
		if (i%2)==0 then
			p2=selected[i-1]
		elseif ((i%2) ~= 0 and (i ~= #selected)) then
			p2=selected[i+1]
		else -- if i = last individual
			p2 = selected[i-1]
		end
		child = crossoverDoublePoint(p1, p2)
		mutantChild = mutation(child)
		table.insert(pop, mutantChild)
		
	end -- for loop
	return pop
end

function mutation(str)
	local s = ""
	for i=1, #str do
		local c = str:sub(i,i)
		if math.random() < mutationRate then
			a = math.random()
			
			if (c == "1") then
				if a < 0.33 then
					s = s .. "2"
				elseif a > 0.33 and a < 0.66 then
					s = s .. "3"
				else
					s = s .. "4"
				end
				--s = s .. "3" -- old
			elseif (c == "2") then
				if a < 0.33 then
					s = s .. "1"
				elseif a > 0.33 and a < 0.66 then
					s = s .. "3"
				else
					s = s .. "4"
				end
				--s = s .. "1" -- old
			elseif (c == "3") then
				if a < 0.33 then
					s = s .. "2"
				elseif a > 0.33 and a < 0.66 then
					s = s .. "1"
				else
					s = s .. "4"
				end
				--s = s .. "2" -- old
			elseif (c == "4") then
				if a < 0.33 then
					s = s .. "2"
				elseif a > 0.33 and a < 0.66 then
					s = s .. "3"
				else
					s = s .. "1"
				end
				--s = s .. "1" -- old
			end
		else
			s = s .. c
		end
	end
	return s
end

function crossoverUniform(a,b)
	if math.random() > crossoverRate then	-- returns p1 instead of breeding
		return "" .. a
	end
	local child = ""
	for i=1, #a do
		if math.random() > 0.5 then
			child = child .. a:sub(i,i)
		else
			child = child .. b:sub(i,i)
		end
	end
	
	return child
end

function crossoverDoublePoint(a,b)
	if math.random() > crossoverRate then	-- returns p1 instead of breeding
		return "" .. a
	end
	local child = ""
	local first = math.random(a:len())
	local second = math.random(a:len())
		-- in case 1st cut point == 2nd cut point
	while (first == second) do first = math.random(a:len()) end
	
	if (first < second) then 
		startPos = first
		endPos = second
	else 
		startPos = second
		endPos = first
	end
	
	for i=1, startPos do
		child = child .. a:sub(i,i)
	end
	for i=startPos+1, endPos do
		child = child .. b:sub(i,i)
	end
	for i=endPos+1, a:len() do
		child = child .. a:sub(i,i)
	end
	if #child ~= #a then
		emu.message("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
		emu.message("ERROR: Child length not equal to parent length.")
	end
	return child
end

-- we run up to #population instead of #fitnesses b/c fitnesses list hasn't been culled yet
function getFitnesses(population, fitnesses)
	emu.message("num of elements in population is " .. #population)
	--emu.message("num of elements in fitnesses is " .. #fitnesses)
	for i=1, #population do
		emu.message("for string " .. i .. ", fitness is " .. fitnesses[i] .. " and length of string is " .. #population[i])

	end
end

function wiseSelection(originalPopulation, fitnesses)
	local pop = {}
	repeat
		local bestString = nil
		local bestFitness = 0
		for i=1, tournamentSize do
		
			local selection = math.random(#fitnesses)
			if fitnesses[selection] > bestFitness then
				bestFitness = fitnesses[selection]
				bestString = originalPopulation[selection]
			end
		end
		table.insert(pop, bestString)
	-- we retain both the fittest individual from the population as well as an individual aggregated from the top 20%
	-- n-2 because we're gonna have a wise individual and an elite individual
	until #pop == populationSize -3 -- TODO We're leaving space for WoC/elite
	return pop
end

-- select a random fitness and if its better than current best, make it new current best + say the best string is the member with that fitness. Insert that member into the new population.
function selection(originalPopulation, fitnesses)
	local pop = {}
	repeat
		local bestString = nil
		local bestFitness = 0
		for i=1, tournamentSize do
			-- select from the table of fitnesses
			local selection = math.random(#fitnesses)
			-- if fitness AT selection is better than the best, say that's the best
			-- fitness, and the solution with that fitness is now the best solution
			if fitnesses[selection] > bestFitness then
				bestFitness = fitnesses[selection]
				bestString = originalPopulation[selection]
			end
		end
		-- when we're done selecting the parents, put them in a new population of parents
		table.insert(pop, bestString)
	until #pop == #originalPopulation -- #originalPopulation = populationSize
	return pop
end

-- TODO There's probably a point at which getFitness() is being called, and there's nothing in element 1 (currentIndividual)
-- 		in the fitnesses array, b/c it's been wiped. Why is getFittest() being called when fitnesses is empty?

function getFittest(currentBest, fromPopulation, fitnesses)
	-- bestScore will be 0 if currentBest is nil, or currentBest if it's not nil
	-- (we're initializing the fittest value as the first solution in the table,
	-- or just 0 if this is the first time we're calling getFittest())
	--emu.message("getFittest(): length of fitnesses is " .. #fitnesses)
	
	local bestScore = (currentBest == nil and 0) or getFitness(fitnesses, currentIndividual)
	
	if not bestScore then
		emu.message("------------------ bestScore is nil -----------------")
		emu.message("#fitnesses is " .. #fitnesses)
	end
	
	
	local best = currentBest
	for i,j in ipairs(fitnesses) do
	--	emu.message("type of bestScore is " .. type(bestScore))
	--	emu.message("Type of j is " .. type(j))
	--	emu.message("currentIndividual is #" .. currentIndividual)
	--	emu.message("#fitnesses is " .. #fitnesses)
		if (j > bestScore) then
			bestScore = j
			best = fromPopulation[i]
		end
	end
	totalBestScore = bestScore
	return best
end

function getFitness(fitnesses, i)
	return fitnesses[i]
end

function outputScores()
	-- write scores and their respective input strings to a file for logging
	-- create script/button/something that calls readInput for a user-given input string
end


-- os.time() is in terms of seconds, and os.clock() is in terms of seconds from the first time it was called
function guiAdvance()
	
	emu.frameadvance()
	currentRun = string.format(os.clock() - time)
	--gui.text(175,10, "XPos " .. memory.readbyte(0x071C))
	--gui.text(85,10, "globalX " .. globalX)
	
	-- Set a flag true indicating we marked (incremented) globalX, and set it = false when 0.2 seconds have passed
	if (memory.readbyte(0x071C) > 250) and (xmarked == false) then
		--io.write("\nincrementing globalX at time " .. currentRun .. "\n")
		globalX = globalX + 1
		xmarked = true		
		startTime = os.clock()
	end
	
	if (os.clock() - startTime >= 0.2) and (xmarked == true) then
		xmarked = false
	end
	
	gui.text(5,220, currentRun)
	--gui.text(140,10, "Distance " .. memory.readbyte(0x006D))
	
	gui.text(5,10, "Previous Gen Best: " .. totalBestScore)
			--gui.text(180,210, "Penalty " .. penalty)
	
	gui.text(5,210, string.format(os.clock() - totalTime))
	gui.text(95,210, "Parent Pop: PS/4 = " .. tournamentSize)
	gui.text(85,220, "Generation " .. currentGeneration .. "/" .. generations)
	gui.text(180,220, "Individual " .. currentIndividual .. "/" .. populationSize)
end	

function getScore()
	-- get score in several bytes, concatenate and return them, fitness is just score
	s1 = memory.readbyte(0x07DD)
	s2 = memory.readbyte(0x07DE)
	s3 = memory.readbyte(0x07DF)
	s4 = memory.readbyte(0x07E0)
	s5 = memory.readbyte(0x07E1)
	s6 = memory.readbyte(0x07E2)
	s7 = memory.readbyte(0x07E3)
	score = s1 .. s2 .. s3 .. s4 .. s5 .. s6 .. s7
	score = tonumber(score)
	
	distance = (globalX * 255) + memory.readbyte(0x071C)
	-- Keeps track of distance Mario has traveled 
	-- 0x071C is Mario's x-position. Resets after 255.
	score = score + distance - penalty-- - timeSpent
	-- 0x071C moves much faster than timeSpent, so it overtakes it
	
	if (score < 0) then
		score = 0
	end
	
	return score
end

function randomString(goalLength)
	str = ""
	while (str:len() < goalLength) do
		r = math.random() * 10
		if r < 2 then
			str = str .. "1"	-- 20% chance of running right		
		elseif r < 4 then
			str = str .. "2"	-- 20% chance of jumping
		elseif r <= 8.5 then
			str = str .. "3"	-- 45% chance of runjumping
		elseif r > 8.5 then
			str = str .. "4"	-- 15% chance of running left
		else
			emu.message("Error: random length out of bounds.")
		end
	end
	return str
end

function readInput(inputString)
	lastPos = memory.readbyte(0x0086)
	time = os.clock()
		for i = 1, #inputString do
			if (memory.readbyte(0x000E) == 11) or ( memory.readbyte(0x00B5) > 1) then 
				memory.writebyte(0x000E, 11)
				break 
			end
			local c = inputString:sub(i,i)
			if (c == "1") then
				for j=1, 20 do
					joypad.set(1, {right = true})
					guiAdvance()
				end
			elseif (c == "2") then
				for j=1, 8 do	
					joypad.set(1, {A = true})
					guiAdvance()
				end
				lastPos = memory.readbyte(0x0086)
			elseif (c == "3") then
				for j=1, 20 do
					joypad.set(1, {A = true, right = true})
					guiAdvance()
				end
			elseif (c == "4") then
				for j=1, 20 do
					joypad.set(1, {left = true})
					guiAdvance()
				end
				
				lastPos = memory.readbyte(0x0086)
			else
				emu.message("Error: c = " .. c)
			end
		end -- for loop
		
		if (memory.readbyte(0x000E) ~= 11) then
			emu.message("End of this individual's input string and Mario hasn't died. Killing Mario...")
			penalty = 800
			memory.writebyte(0x000E, 11) -- kill Mario
		end
end

function death()
	
	local score = getScore()
	writeScore(score)
	emu.message("---------------------------------------------")
	emu.message("died, score " .. score .. ", distance " .. memory.readbyte(0x006D) .. ", globalX " .. globalX .. ", x-pos " .. memory.readbyte(0x071C) .. " Gen " .. currentGeneration .. " Individual " .. currentIndividual)
	
	currentIndividual = currentIndividual+1
	table.insert(fitnesses, score)
	savestate.load(save)
	emu.message("totalTime: " .. os.clock() - totalTime .. ", time spent: " .. os.clock() - time)
	time = os.clock() --string.format("%f", os.clock())
	globalX = 0
end

function writeScore(currentScore)
	file = io.open("scores.txt", "a")
	-- sets file as default output file
	io.output(file)
	
	io.write(currentScore .. "\n")
	
	io.close(file)
end

function writeGeneration()
	file = io.open("scores.txt", "a")
	io.output(file)
	io.write("Generation " .. currentGeneration .. "\n")
	io.close(file)
end

function writeToFile()
	file = io.open("scores.txt", "a")
	-- sets file as default output file
	io.output(file)
	io.write(totalBestScore .. "\n")
	io.close(file)
end

function finish()
	io.write("\n")
	emu.message("Total elapsed time: " .. totalTime)
	local dist = memory.readbyte(0x006D) -- .. "\n" why was this \n here?
	local score = getScore(dist)
	fittest = getFittest(fittest, population, fitnesses)
	io.write(string.format("The fittest member of the population is the string: \n"))
	io.write(string.format(fittest))
	io.write(string.format("\nwith a fitness score of: \n"))
	io.write(string.format(totalBestScore))
	emu.message(" ")
	emu.pause()
	
	if (input.popup("Do you wish to replay the best solution?") == "yes") then
		emu.unpause()
		readInput(fittest)	-- run again
		finish()
	end
end

function printLengths(population)
	for i=1, #population do
		emu.message("length of individual " .. i .. " is " .. #population[i])
	end
end

------------------------
---		Start	     ---
---	Initializations! ---
------------------------
time = os.clock()
totalTime = os.clock()
currentGeneration = 1
currentIndividual = 1
totalBestScore = 0
penalty = 0
timeLeft = -1
timeSpent = -1

population = { }
fittest = nil
for i=1, populationSize do
	table.insert(population, randomString(problemSize))
	for j=1, 20 do
		-- waste a little bit of time so that the random numbers aren't all the same
	end
end
currentProblem = population[1]
fitnesses = {}
joypad.set(1, {start=true})
for i=1, 200 do
	guiAdvance()
end

time = os.clock()
totalTime = os.clock()
save = savestate.create(1)
lastPos = memory.readbyte(0x0086)
while (true) do																-- TODO Implement elitism, floor(top 10%)

	if (currentIndividual == populationSize + 1) then
		currentGeneration = currentGeneration + 1
		
		if (currentGeneration == generations) then finish() break end
		
		globalX = 0
		currentIndividual = 1
		elementsToErase = (currentGeneration-1) * populationSize
		
		emu.message("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
		emu.message("Starting evolution for new generation.")
		emu.message("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
		
		writeGeneration()
		
		fittest = getFittest(fittest, population, fitnesses)
		writeToFile()
		
		emu.message("Fittest individual from that gen was:")
		emu.message(fittest)
		
		parentPop = wiseSelection(population, fitnesses)
		
		fitnesses = subrange(fitnesses, elementsToErase+1, #fitnesses)
		superIndividual = aggregate()
				
		table.insert(parentPop, fittest) -- was population
		
		population = reproduce(parentPop)
		table.insert(population, superIndividual)
		
		-- TODO These individuals should at least be mutated, right now they're added to the child population after breeding/mutation
		-- Do we want the fittest individual to stay and breed, until even more fit individuals are created?
		
		-- TODO Average out the fitnesses from each generation to create a chart of improvement
		
	
		table.insert(population, fittest)
		
				--emu.message("#population after inserting fittest again: " .. #population)
		
		for i=1, 20 do
			guiAdvance()
		end
	end

	if (memory.readbyte(0x000E) ~= 11 and memory.readbyte(0x00B5) <= 1) then
		if (lastPos == memory.readbyte(0x0086) and memory.readbyte(0x0001) == 79) then
				joypad.write(1, {right = true})				
				guiAdvance()
	--		end
		else
			----------------------
			-- player is moving --
			----------------------
			penalty = 0
		--	emu.message("calling readInput() with current individual = " .. currentIndividual .. ", #population = " .. #population)
			readInput(population[currentIndividual])
		--	time = os.time()
			lastPos = memory.readbyte(0x0086)
		end
	else
		-----------------
		-- player died --
		-----------------
		death(score)
		guiAdvance()
	end
end

-- new generation: getFittest() -> wiseSelection() -> reproduce() -> crossover() -> mutation() -> insert into population
-- Don't need to keep track of populationSize * generations # of fitness scores b/c last generation will be fitter than previous

-- Single-Point Crossover:
-- select randomized index to cut p1's string,
		-- make child = 1st half of p2, 2nd half of p2
	--local cut = math.random(a:len() - 1)
	--local child = ""
	--for i=1, cut do
	--	child = child .. a:sub(i,i)
	--end
	--for i = cut+1, b:len() do
	--	child = child .. b:sub(i,i)
	--end

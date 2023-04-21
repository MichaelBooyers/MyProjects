from random import randrange
#starts the random numbers
firstDie = 0
#1st scoring component of game
secondDie = 0
#2nd scoring component of game
total = 0
#The total score of the game counting the users current rolls before saving
grandScore = 0
#The saved score a player can have when they type 'Quit'
turns = 0
#Each time a user types 'Roll' this is a turn and the program keep updates of this
pastScore = 0
#This will be the score a user just rolled, will be compared to the current score and can double
currentScore = 0
#This is the total of the one roll the user just rolled, it is compared to the last score and can double
firstDieAI = 0
#1st scoring component of game
secondDieAI = 0
#2nd scoring component of game
totalAI = 0
#The total score of the game counting the users current rolls before saving
grandScoreAI = 0
#The saved score a player can have when they type 'Quit'
turnsAI = 0
#Each time a user types 'Roll' this is a turn and the program keep updates of this
pastScoreAI = 0
#This will be the score a user just rolled, will be compared to the current score and can double
currentScoreAI = 0
#This is the total of the one roll the user just rolled, it is compared to the last score and can double
done = True
gameOver = False
userInput = 0
#Asks the user to start the game
	
userInput = input('Type "Roll" to begin! ')

while done == True:
	while userInput == 'Roll':
		print('')
		pastScore = currentScore
		turns += 1
		firstDie = randrange(1,7)
		secondDie = randrange(1,7)
		print('Your first die was a:', firstDie)
		print('Your second die was a:', secondDie)
		print('Your total from this roll is:', firstDie + secondDie)
		total = total + firstDie + secondDie
		currentScore = 0
		currentScore = firstDie + secondDie
		#This gets the total of the die and begins to set

		if currentScore == pastScore:
			print('')
			print('Your last two rolls scored the same!')
			print('You doubled your current total of points!')
			print('Your old in-game total was:', total)
			total *= 2
			print('Your new in-game total is:', total)

		if (firstDie + secondDie == 7): 
			total = 0
			currentScore = 0
			pastScore = 0
			print('You lost your current score!')
			done = False
		if (grandScore + total >= 200):
			userInput = 'Done'
			final = grandScore + total
			print('Game over!')
			print('Your total at the end was:',final )
			print('It took', turns, 'turns to get 200!')
			break
		else:
			print('Your current score is:', grandScore + total)
			print('You have used', turns, 'roll(s) so far!')
			print('')

		if done == True:
			userInput = input('Type "Roll" to try again or type "Quit" to save score! ' )
			while userInput != 'Roll' and userInput != 'Quit':
				print('Typo detected:', userInput)
				userInput = input('Type "Roll" to begin! ')

		if userInput == 'Quit':
			grandScore += total
			pastScore = 0
			total = 0
			print('Your saved score is:', grandScore)
			print('')
			done = False

		while done == False:

			print('')
			pastScoreAI = currentScoreAI
			turnsAI += 1
			firstDieAI = randrange(1,7)
			secondDieAI = randrange(1,7)
			print("The AI's first die was a:", firstDieAI)
			print("The AI's second die was a:", secondDieAI)
			print("The AI's total from this roll is:", firstDieAI + secondDieAI)
			totalAI = totalAI + firstDieAI + secondDieAI
			currentScoreAI = 0
			currentScoreAI = firstDieAI + secondDieAI
			#This gets the total of the die and begins to set

			if currentScoreAI == pastScoreAI:
				print('')
				print("The AI's last two rolls scored the same!")
				print("The AI doubled it's current total of points!")
				print('Their old in-game total was:', totalAI)
				totalAI *= 2
				print("Now it's new in-game total is:", totalAI)

			if (grandScoreAI + totalAI >= 200):
				finalAI = grandScoreAI + totalAI
				print('Game over!')
				print('The total for the AI at the end was:',finalAI )
				print('It took', turnsAI, 'turns to get 200 for the AI!')
				break
			else:
				print("The AI's current score is:", grandScoreAI + totalAI)
				print('The AI has used', turnsAI, 'roll(s) so far!')
				print('')

			if (firstDieAI + secondDieAI == 7): 
				totalAI = 0
				pastScoreAI = 0
				print("The AI lost it's current score!")
				userInput = input('Type "Roll" to begin! ')
				done = True
		
			if ((totalAI + grandScoreAI) + 20) < grandScore + total or (grandScore + total) >= 180:
				done = False 
			elif totalAI >= randrange(20,31) and totalAI + grandScoreAI > grandScore + total:
				grandScoreAI += totalAI
				pastScoreAI = 0
				totalAI = 0
				currentScoreAI = 0
				print("The AI's saved score is:", grandScoreAI)
				print('')
				userInput = input('Type "Roll" to begin! ')
				done = True

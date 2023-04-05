#include "VMEngine2D/GameState.h"
#include "VMEngine2D/GameObject.h"
#include "SDL2/SDL.h"
#include "VMEngine2D/Text.h"

GameState::GameState(SDL_Window* Window, SDL_Renderer* Renderer)
{
	StateWindow = Window;
	StateRenderer = Renderer;
	bHasActivated = false;
}

GameState::~GameState()
{
	for (Text* SingleText : StateTextObjects) {
		delete SingleText;
	}
	StateTextObjects.clear();
}

void GameState::ProcessInput(Input* PlayerInput)
{
	if (!bHasActivated) {
		return;
	}

	//process the input  of each gameobject
	for (GameObject* SingleGameObject : StateGameObject) {
		SingleGameObject->ProcessInput(PlayerInput);
	}
}

void GameState::Update(float DeltaTime)
{
	if (!bHasActivated) {
		bHasActivated = true;
			BeginState();
	}

	//run last gameobject logic
	for (GameObject* SingleGameObject : StateGameObject) {
		SingleGameObject->Update();
	}

	
}

void GameState::Draw(SDL_Renderer* Renderer)
{
	if (!bHasActivated) {
		return;
	}
	
	//cycle through all of the gameObjects in the ALLGameObjects array
	//each loop reassign the singleGameobject
	for (GameObject* SingleGameObject : StateGameObject) {
		//each loop run the draw function for each gameobject
		SingleGameObject->Draw(Renderer);
	}
	//
	//
	for (Text* SingleText : StateTextObjects) {
		SingleText->Draw(Renderer);
	}
}

void GameState::HandleGarbage()
{
	if (!bHasActivated) {
		return;
	}

	//loop thru all of the gameoobject and assign the iterator each loop
	for (GOIterator Object = StateGameObject.begin(); Object != StateGameObject.end();) {
		//if the object is not marked for delte then increment and skip to the next one
		if (!(*Object)->ShouldDestroy()) {
			Object++;
			continue;
		}

		//delete the gamobject
		delete* Object;

		//remove the object from the array and resize the array
		Object = StateGameObject.erase(Object);

		std::cout << "delte gameObject" << std::endl;
	}
}

void GameState::AddCollisionToGameState(CollisionComponent* Collision)
{
	StateCollision.push_back(Collision);
}

void GameState::RemoveCollisionFromGameState(CollisionComponent* Collision)
{
	//the find function finds an object or data using the object in a vector stack
	//@Param 1 - look from the start of the array
	//@Param 2 - to trhe end of the array
	//@Param 3 - the object that we aare searching for
	ColIterator ColToRemove = std::find(StateCollision.begin(), StateCollision.end(), Collision);

	//the  find function will set the iterator to allcolliders .end() if it didnt find anything
	if (ColToRemove == StateCollision.end()) {
		//didnt find the collision
		return;//return will kill the rest of the function if its run
	}

	//remove the collidier if the fiind funtion found the collider
	StateCollision.erase(ColToRemove);
}

void GameState::BeginState()
{

}

void GameState::EndState()
{

	for (GameObject* SingleGameObject : StateGameObject) {
		SingleGameObject->DestroyGameObject();
	}


	//run the handle garbage to delete
	HandleGarbage();
}

void GameState::ActivateGameObject(GameObject* ObjectToAdd)
{
	StateGameObject.push_back(ObjectToAdd);

}

void GameState::ActivateTextObject(Text* TextToAdd)
{
	StateTextObjects.push_back(TextToAdd);
}

//////////////////////////GAMESTATE MACHINE //////////////////////////////////////

GameStateMachine::GameStateMachine(GameState* StartingState)
{
	SwitchState(StartingState);
}

GameStateMachine::~GameStateMachine()
{
	//run through a;ll the states, end them, then delete them
	for (GameState* SingleGameState : GameStateStack) {
		SingleGameState->EndState();
		delete SingleGameState;
	}

	//clear the stack
	GameStateStack.clear();
}

void GameStateMachine::SwitchState(GameState* NewState)
{
	//take out the current top state
	PopState();
	//add in a new state
	PushState(NewState);
}

void GameStateMachine::PushState(GameState* NewState)
{
	//add the state to the top of the stack
	GameStateStack.push_back(NewState);
}

void GameStateMachine::PopState()
{
	if (GameStateStack.size() > 1) {
		//cache the old state so we can delet it after it is removed
		GameState* OldState = GetCurrentState();
		//remove it from stack
		GameStateStack.pop_back();
		//end the oldstate then delete it
		OldState->EndState();
		delete OldState;
	}
}

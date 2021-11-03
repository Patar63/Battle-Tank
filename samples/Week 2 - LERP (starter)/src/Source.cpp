/*
Week 2 tutorial sample - LERP
Quinn Daggett 2021
*/

#include "NOU/App.h"
#include "NOU/Input.h"
#include "NOU/Entity.h"
#include "NOU/CCamera.h"
#include "NOU/CMeshRenderer.h"
#include "NOU/Shader.h"
#include "NOU/GLTFLoader.h"

#include "Logging.h"

#include <memory>

using namespace nou;

// TODO: create a templated LERP function
template <typename T>
T lerp(T a, T b, float t) 
{
	return(1.0f - t) * a + b * t;
}

int main()
{
	// Create window and set clear color
	App::Init("Week 2 tutorial - LERP", 800, 600);
	App::SetClearColor(glm::vec4(0.0f, 0.27f, 0.4f, 1.0f));

	App::Tick();

	// Load vertex and fragment shaders
	std::unique_ptr vs_litShader = std::make_unique<Shader>("shaders/texturedlit.vert", GL_VERTEX_SHADER);
	std::unique_ptr fs_litShader = std::make_unique<Shader>("shaders/texturedlit.frag", GL_FRAGMENT_SHADER);

	// Activate shader program
	ShaderProgram shaderProgram = ShaderProgram({ vs_litShader.get(), fs_litShader.get() });

	// Create and load mesh for duck
	Mesh mesh_duck;
	GLTF::LoadMesh("duck/Duck.gltf", mesh_duck);

	// Create material and load textures for duck
	Texture2D text2D_duck = Texture2D("duck/DuckCM.png");
	Material mat_duck(shaderProgram);
	mat_duck.AddTexture("albedo", text2D_duck);

	// Create and set up camera
	Entity camera = Entity::Create();
	CCamera& cam = camera.Add<CCamera>(camera);
	cam.Perspective(60.0f, 1.0f, 0.1f, 100.0f);
	camera.transform.m_pos = glm::vec3(0.0f, 0.0f, 4.0f);

	// Creating duck entity
	Entity duck = Entity::Create();
	duck.Add<CMeshRenderer>(duck, mesh_duck, mat_duck);
	duck.transform.m_scale = glm::vec3(0.005f, 0.005f, 0.005f);
	duck.transform.m_pos = glm::vec3(0.0f, -1.0f, 0.0f);
	duck.transform.m_rotation = glm::angleAxis(glm::radians(-30.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	// TODO: define necessary variables for LERPing
	glm::vec3 startScale = glm::vec3(0.005f);
	glm::vec3 startPos = glm::vec3(0.0f, -1.0f, 0.0f);
	float startRot = -30.0;

	glm::vec3 endScale = glm::vec3(0.030f);
	glm::vec3 endPos = glm::vec3(5.0f, 2.0f, 0.0f);
	float endRot = 330.0;

	//Interpelation Perameter
	float Time = 0.0f;
	float loop = 1.0f;

	// Main loop
	while (!App::IsClosing() && !Input::GetKeyDown(GLFW_KEY_ESCAPE))
	{
		App::FrameStart();
		float deltaTime = App::GetDeltaTime();

		// TODO: LERP duck properties
		Time += deltaTime * loop;

		if (Time > 1.0f || Time < 0.0f)
		{
			loop *= -1.0f;
		}

		duck.transform.m_scale = lerp(startScale, endScale, Time);
		duck.transform.m_pos = lerp(startPos, endPos, Time);
		duck.transform.m_rotation = glm::angleAxis(glm::radians(lerp(startRot, endRot, Time)), glm::vec3(0.0f, 1.0f, 0.0f));

		// update camera and duck, draw duck
		camera.Get<CCamera>().Update();

		duck.transform.RecomputeGlobal();

		duck.Get<CMeshRenderer>().Draw();

		// Draw everything we just did to the screen
		App::SwapBuffers();
	}

	// Destroy window
	App::Cleanup();

	return 0;
}
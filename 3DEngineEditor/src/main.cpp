#include<iostream>
#include<memory>
#include"3DEngineCore/Application.hpp"


// задача параметров для выполнения функционала движка

int main(){

	std::cout << "3D engine editor" << std::endl;

	Engine::Application Myapp;
	Myapp.start(1024,768,"SYKA");
	std::cin.get();
}
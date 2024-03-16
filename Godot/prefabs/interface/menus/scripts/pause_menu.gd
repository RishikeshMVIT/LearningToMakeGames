extends Control

func _on_continue_button_pressed() -> void:
	GameManager.resume_game()


func _on_menu_button_pressed() -> void:
	GameManager.exit_game()

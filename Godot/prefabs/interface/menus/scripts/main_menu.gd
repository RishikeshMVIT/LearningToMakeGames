extends Control

func _on_play_button_pressed() -> void:
	GameManager.start_game()


func _on_settings_button_pressed() -> void:
	pass # Replace with function body.


func _on_quit_button_pressed() -> void:
	GameManager.quit_game()

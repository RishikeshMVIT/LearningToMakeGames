// Copyright (c) Sandbox 2024. All rights reserved

using UnityEditor;

namespace Sandbox
{
    /// <summary>
    /// SetAnimatorFirstFrame
    /// </summary>
    public class SetAnimatorFirstFrame
    {
        [MenuItem("Assets/Tools/Animation/Set First Frame")]
        [MenuItem("Tools/Animation/Set First Frame")]
        public static void SetFirstFrameMenuOption()
        {

        }

        [MenuItem("Assets/Tools/Animation/Set First Frame", validate = true)]
        [MenuItem("Tools/Animation/Set First Frame", validate = true)]
        public static bool SetFirstFrameMenuOptionValidate()
        {
            return true;
        }
    }
}

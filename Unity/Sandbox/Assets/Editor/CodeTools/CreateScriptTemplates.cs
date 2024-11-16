// Copyright (c) Sandbox 2024. All rights reserved

using UnityEditor;

namespace Sandbox
{
    /// <summary>
    /// CreateScriptTemplates
    /// </summary>
    public static class CreateScriptTemplates
    {
        [MenuItem("Assets/Create/Code/Monobehaviour", priority = 40)]
        public static void CreateMonobehaviourMenuItem()
        {
            string templatePath = "Assets/Editor/CodeTools/Templates/Monobehaviour.cs.txt";

            ProjectWindowUtil.CreateScriptAssetFromTemplateFile(templatePath, "NewMonobehaviour.cs");
        }

        [MenuItem("Assets/Create/Code/Interface", priority = 39)]
        public static void CreateInterfaceMenuItem()
        {
            string templatePath = "Assets/Editor/CodeTools/Templates/Interface.cs.txt";

            ProjectWindowUtil.CreateScriptAssetFromTemplateFile(templatePath, "NewInterface.cs");
        }

        [MenuItem("Assets/Create/Code/Class", priority = 38)]
        public static void CreateClassMenuItem()
        {
            string templatePath = "Assets/Editor/CodeTools/Templates/Class.cs.txt";

            ProjectWindowUtil.CreateScriptAssetFromTemplateFile(templatePath, "NewClass.cs");
        }

        [MenuItem("Assets/Create/Code/Enum", priority = 38)]
        public static void CreateEnumMenuItem()
        {
            string templatePath = "Assets/Editor/CodeTools/Templates/Enum.cs.txt";

            ProjectWindowUtil.CreateScriptAssetFromTemplateFile(templatePath, "NewEnum.cs");
        }

        [MenuItem("Assets/Create/Code/EditorScript", priority = 37)]
        public static void CreateEditorScriptMenuItem()
        {
            string templatePath = "Assets/Editor/CodeTools/Templates/EditorScript.cs.txt";

            ProjectWindowUtil.CreateScriptAssetFromTemplateFile(templatePath, "NewEditorScript.cs");
        }

        [MenuItem("Assets/Create/Code/Text", priority = 36)]
        public static void CreateTextFileMenuItem()
        {
            string templatePath = "Assets/Editor/CodeTools/Templates/Text.txt";

            ProjectWindowUtil.CreateScriptAssetFromTemplateFile(templatePath, "NewTextFile.txt");
        }
    }
}

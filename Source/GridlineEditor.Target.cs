using UnrealBuildTool;
public class GridlineEditorTarget : TargetRules {
    public GridlineEditorTarget(TargetInfo Target) : base(Target) {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        ExtraModuleNames.Add("Gridline");
    }
}

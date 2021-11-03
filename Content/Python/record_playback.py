import sys
import unreal


def create_level_sequence_transform_track(asset_name, length_seconds=600, package_path='/Game/'):
    sequence = unreal.AssetToolsHelpers.get_asset_tools().create_asset(asset_name, package_path, unreal.LevelSequence, unreal.LevelSequenceFactoryNew())
    actor_class = unreal.EditorAssetLibrary.load_blueprint_class('/VideoCore/Blueprints/BP_RecordedPlaneBase')
    actor = unreal.EditorLevelLibrary.spawn_actor_from_class(actor_class, [-450.0, 1030.0, 230.0], [0, 0, 0])
    binding = sequence.add_possessable(actor)
    transform_track = binding.add_track(unreal.MovieScene3DTransformTrack)
    transform_section = transform_track.add_section()
    transform_section.set_start_frame_seconds(0)
    transform_section.set_end_frame_seconds(length_seconds)
    
    ## now do media track
    media_track = sequence.add_master_track(unreal.MovieSceneMediaTrack)
    media_track.set_editor_property("display_name", "Media")
    media_section = media_track.add_section()
    img_source = unreal.AssetToolsHelpers.get_asset_tools().create_asset("MS_" + asset_name, '/Game', unreal.ImgMediaSource, None)
    image_path = unreal.SystemLibrary.get_project_content_directory() + "/Movies/NewImageSequence/1.png"
    img_source.set_sequence_path(image_path)
    media_section.media_source = img_source
    media_texture = unreal.AssetToolsHelpers.get_asset_tools().create_asset("MT_" + asset_name, '/Game/', unreal.MediaTexture, unreal.MediaTextureFactoryNew())
    media_section.media_texture = media_texture
    media_section.set_range(0,30)
    
    # Now create a new material instance (from base chromakey bat) and apply to newly created actor
    material_instance = unreal.AssetToolsHelpers.get_asset_tools().create_asset("MI_" + asset_name, '/Game/', unreal.MaterialInstanceConstant, unreal.MaterialInstanceConstantFactoryNew())
    base_material = unreal.load_asset('/VideoCore/Materials/M_CamChroma')
    material_instance.set_editor_property('parent', base_material)
    media_texture = unreal.load_asset('/Game/'+"MT_" + asset_name)
    unreal.MaterialEditingLibrary.set_material_instance_texture_parameter_value(material_instance, 'Texture', media_texture)
    unreal.MaterialEditingLibrary.update_material_instance(material_instance)
    
    placeholder_mat = unreal.load_asset('/Engine/BasicShapes/BasicShapeMaterial')
    unreal.EditorLevelLibrary.replace_mesh_components_materials_on_actors([actor], placeholder_mat, material_instance)

    return sequence


def add_transform_keys(sequence):
    transforms = []
    float_list = []
    transform_path = unreal.SystemLibrary.get_project_content_directory() + '/Python/RecordedTransforms.txt'
    with open(transform_path, 'r') as (f):
        for line in f:
            line.strip()
            line = line.split('|')
            for item in line:
                new_item = item.split(',')
                for i in new_item:
                    i.strip()
                    float_list.append(float(i))

    n = 9
    for i in xrange(0, len(float_list), n):
        transforms.append(float_list[i:i + n])

    print transforms
    for binding in sequence.get_bindings():
        for track in binding.get_tracks():
            print track
            for section in track.get_sections():
                print '\tSection: ' + section.get_name()
                for channel in section.get_channels():
                    print '\tChannel: ' + channel.get_name()
                    name = channel.get_name()
                    if name == 'Location.X':
                        add_keys_to_transform_channel(0, transforms, channel)
                    elif name == 'Location.Y':
                        add_keys_to_transform_channel(1, transforms, channel)
                    elif name == 'Location.Z':
                        add_keys_to_transform_channel(2, transforms, channel)
                    elif name == 'Rotation.X':
                        add_keys_to_transform_channel(3, transforms, channel)
                    elif name == 'Rotation.Y':
                        add_keys_to_transform_channel(4, transforms, channel)
                    elif name == 'Rotation.Z':
                        add_keys_to_transform_channel(5, transforms, channel)
                    elif name == 'Scale.X':
                        add_keys_to_transform_channel(6, transforms, channel)
                    elif name == 'Scale.Y':
                        add_keys_to_transform_channel(7, transforms, channel)
                    elif name == 'Scale.Z':
                        add_keys_to_transform_channel(8, transforms, channel)


def add_keys_to_transform_channel(transform_component, transforms, channel):
    frame_number = unreal.FrameNumber()
    idx = 0
    for transform in transforms:
        val = transform[transform_component]
        channel.add_key(unreal.TimeManagementLibrary.add_frame_number_integer(frame_number, idx), val)
        idx += 1


if __name__ == "__main__":
    asset_name = sys.argv[1]
    sequence = create_level_sequence_transform_track(asset_name)
    add_transform_keys(sequence)
    

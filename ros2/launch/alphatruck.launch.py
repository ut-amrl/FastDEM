"""FastDEM elevation mapping launch for Alphatruck + SuperOdometry."""

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    pkg_share = FindPackageShare('fastdem_ros2')
    config_file = PathJoinSubstitution([pkg_share, 'config', 'alphatruck.yaml'])
    rviz_config = PathJoinSubstitution([pkg_share, 'launch', 'rviz', 'fastdem_local.rviz'])

    return LaunchDescription([
        DeclareLaunchArgument(
            'input_scan', default_value='',
            description='Override input topic (empty = use alphatruck config)'),
        DeclareLaunchArgument(
            'rviz', default_value='false',
            description='Launch RViz2 for visualization'),

        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            name='fastdem_livox_to_sensor_tf',
            arguments=[
                '0', '0', '0',
                '0', '0', '0',
                'sensor', 'base_link',
            ],
        ),

        Node(
            package='fastdem_ros2',
            executable='fastdem_node',
            name='fastdem',
            output='screen',
            parameters=[{
                'use_sim_time': False,
                'config_file': config_file,
                'input_scan': LaunchConfiguration('input_scan'),
            }],
        ),

        Node(
            package='rviz2',
            executable='rviz2',
            name='rviz2',
            arguments=['-d', rviz_config],
            condition=IfCondition(LaunchConfiguration('rviz')),
        ),
    ])

#  
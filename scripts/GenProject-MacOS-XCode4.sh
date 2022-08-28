pushd $(dirname "$0")/../
exec vendor/premake/premake5 xcode4
popd

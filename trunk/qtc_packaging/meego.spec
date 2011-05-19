Summary:   Display basic Qt-related information in an easy-to-report-to-developer way
Name:      qtinfo
Version:   2.1
Release:   1
Group:     Development/Tools
License:   BSD
URL:       https://projects.forum.nokia.com/qtinfo
Source:    %{name}-%{version}.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root
BuildRequires: qt-devel
BuildRequires: qt-mobility-devel
BuildRequires: libqtopengl-devel
BuildRequires: libqtwebkit-devel

%description
Display basic Qt-related information in an easy-to-report-to-developer way

%prep
%setup -q -n %{name}-%{version}

%build
qmake QtInfo.pro
make %{?_smp_mflags}

%install
%{__rm} -rf $RPM_BUILD_ROOT
qmake QtInfo.pro
make %{?_smp_mflags} INSTALL_ROOT=%{buildroot} install

%clean
%{__rm} -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
#%{_bindir}/%{name}
%{_datadir}/applications/%{name}.desktop
/opt/qtinfo/bin/libglinfolib.so
/opt/qtinfo/bin/libglinfolib.so.1
/opt/qtinfo/bin/libglinfolib.so.1.0
/opt/qtinfo/bin/libglinfolib.so.1.0.0
/opt/qtinfo/bin/libmobilityinfolib.so
/opt/qtinfo/bin/libmobilityinfolib.so.1
/opt/qtinfo/bin/libmobilityinfolib.so.1.0
/opt/qtinfo/bin/libmobilityinfolib.so.1.0.0
/opt/qtinfo/bin/libmultimediainfolib.so
/opt/qtinfo/bin/libmultimediainfolib.so.1
/opt/qtinfo/bin/libmultimediainfolib.so.1.0
/opt/qtinfo/bin/libmultimediainfolib.so.1.0.0
/opt/qtinfo/bin/libqtquickinfolib.so
/opt/qtinfo/bin/libqtquickinfolib.so.1
/opt/qtinfo/bin/libqtquickinfolib.so.1.0
/opt/qtinfo/bin/libqtquickinfolib.so.1.0.0
/opt/qtinfo/bin/libsqlinfolib.so
/opt/qtinfo/bin/libsqlinfolib.so.1
/opt/qtinfo/bin/libsqlinfolib.so.1.0
/opt/qtinfo/bin/libsqlinfolib.so.1.0.0
/opt/qtinfo/bin/libwebkitinfolib.so
/opt/qtinfo/bin/libwebkitinfolib.so.1
/opt/qtinfo/bin/libwebkitinfolib.so.1.0
/opt/qtinfo/bin/libwebkitinfolib.so.1.0.0
/opt/qtinfo/bin/qtinfo
/usr/share/themes/base/meegotouch/icons/qtinfo.svg



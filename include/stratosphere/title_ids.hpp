/*
 * Copyright (c) 2018-2019 Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#pragma once
#include <switch.h>

/* System Modules. */
static constexpr u64 TitleId_SystemStart = 0x0100000000000000ul;

static constexpr u64 TitleId_Fs          = 0x0100000000000000ul;
static constexpr u64 TitleId_Loader      = 0x0100000000000001ul;
static constexpr u64 TitleId_Ncm         = 0x0100000000000002ul;
static constexpr u64 TitleId_Pm          = 0x0100000000000003ul;
static constexpr u64 TitleId_Sm          = 0x0100000000000004ul;
static constexpr u64 TitleId_Boot        = 0x0100000000000005ul;
static constexpr u64 TitleId_Usb         = 0x0100000000000006ul;
static constexpr u64 TitleId_Tma         = 0x0100000000000007ul;
static constexpr u64 TitleId_Boot2       = 0x0100000000000008ul;
static constexpr u64 TitleId_Settings    = 0x0100000000000009ul;
static constexpr u64 TitleId_Bus         = 0x010000000000000Aul;
static constexpr u64 TitleId_Bluetooth   = 0x010000000000000Bul;
static constexpr u64 TitleId_Bcat        = 0x010000000000000Cul;
static constexpr u64 TitleId_Dmnt        = 0x010000000000000Dul;
static constexpr u64 TitleId_Friends     = 0x010000000000000Eul;
static constexpr u64 TitleId_Nifm        = 0x010000000000000Ful;
static constexpr u64 TitleId_Ptm         = 0x0100000000000010ul;
static constexpr u64 TitleId_Shell       = 0x0100000000000011ul;
static constexpr u64 TitleId_BsdSockets  = 0x0100000000000012ul;
static constexpr u64 TitleId_Hid         = 0x0100000000000013ul;
static constexpr u64 TitleId_Audio       = 0x0100000000000014ul;
static constexpr u64 TitleId_LogManager  = 0x0100000000000015ul;
static constexpr u64 TitleId_Wlan        = 0x0100000000000016ul;
static constexpr u64 TitleId_Cs          = 0x0100000000000017ul;
static constexpr u64 TitleId_Ldn         = 0x0100000000000018ul;
static constexpr u64 TitleId_NvServices  = 0x0100000000000019ul;
static constexpr u64 TitleId_Pcv         = 0x010000000000001Aul;
static constexpr u64 TitleId_Ppc         = 0x010000000000001Bul;
static constexpr u64 TitleId_NvnFlinger  = 0x010000000000001Cul;
static constexpr u64 TitleId_Pcie        = 0x010000000000001Dul;
static constexpr u64 TitleId_Account     = 0x010000000000001Eul;
static constexpr u64 TitleId_Ns          = 0x010000000000001Ful;
static constexpr u64 TitleId_Nfc         = 0x0100000000000020ul;
static constexpr u64 TitleId_Psc         = 0x0100000000000021ul;
static constexpr u64 TitleId_CapSrv      = 0x0100000000000022ul;
static constexpr u64 TitleId_Am          = 0x0100000000000023ul;
static constexpr u64 TitleId_Ssl         = 0x0100000000000024ul;
static constexpr u64 TitleId_Nim         = 0x0100000000000025ul;
static constexpr u64 TitleId_Cec         = 0x0100000000000026ul;
static constexpr u64 TitleId_Tspm        = 0x0100000000000027ul;
static constexpr u64 TitleId_Spl         = 0x0100000000000028ul;
static constexpr u64 TitleId_Lbl         = 0x0100000000000029ul;
static constexpr u64 TitleId_Btm         = 0x010000000000002Aul;
static constexpr u64 TitleId_Erpt        = 0x010000000000002Bul;
static constexpr u64 TitleId_Time        = 0x010000000000002Cul;
static constexpr u64 TitleId_Vi          = 0x010000000000002Dul;
static constexpr u64 TitleId_Pctl        = 0x010000000000002Eul;
static constexpr u64 TitleId_Npns        = 0x010000000000002Ful;
static constexpr u64 TitleId_Eupld       = 0x0100000000000030ul;
static constexpr u64 TitleId_Arp         = 0x0100000000000031ul;
static constexpr u64 TitleId_Glue        = 0x0100000000000031ul;
static constexpr u64 TitleId_Eclct       = 0x0100000000000032ul;
static constexpr u64 TitleId_Es          = 0x0100000000000033ul;
static constexpr u64 TitleId_Fatal       = 0x0100000000000034ul;
static constexpr u64 TitleId_Grc         = 0x0100000000000035ul;
static constexpr u64 TitleId_Creport     = 0x0100000000000036ul;
static constexpr u64 TitleId_Ro          = 0x0100000000000037ul;
static constexpr u64 TitleId_Profiler    = 0x0100000000000038ul;
static constexpr u64 TitleId_Sdb         = 0x0100000000000039ul;
static constexpr u64 TitleId_Migration   = 0x010000000000003Aul;
static constexpr u64 TitleId_Jit         = 0x010000000000003Bul;
static constexpr u64 TitleId_JpegDec     = 0x010000000000003Cul;
static constexpr u64 TitleId_SafeMode    = 0x010000000000003Dul;
static constexpr u64 TitleId_Olsc        = 0x010000000000003Eul;
static constexpr u64 TitleId_Dt          = 0x010000000000003Ful;
static constexpr u64 TitleId_Nd          = 0x0100000000000040ul;

static constexpr u64 TitleId_SystemEnd   = 0x01000000000007FFul;

/* System Data Archives. */
static constexpr u64 TitleId_ArchiveStart                         = 0x0100000000000800ul;
static constexpr u64 TitleId_ArchiveCertStore                     = 0x0100000000000800ul;
static constexpr u64 TitleId_ArchiveErrorMessage                  = 0x0100000000000801ul;
static constexpr u64 TitleId_ArchiveMiiModel                      = 0x0100000000000802ul;
static constexpr u64 TitleId_ArchiveBrowserDll                    = 0x0100000000000803ul;
static constexpr u64 TitleId_ArchiveHelp                          = 0x0100000000000804ul;
static constexpr u64 TitleId_ArchiveSharedFont                    = 0x0100000000000805ul;
static constexpr u64 TitleId_ArchiveNgWord                        = 0x0100000000000806ul;
static constexpr u64 TitleId_ArchiveSsidList                      = 0x0100000000000807ul;
static constexpr u64 TitleId_ArchiveDictionary                    = 0x0100000000000808ul;
static constexpr u64 TitleId_ArchiveSystemVersion                 = 0x0100000000000809ul;
static constexpr u64 TitleId_ArchiveAvatarImage                   = 0x010000000000080Aul;
static constexpr u64 TitleId_ArchiveLocalNews                     = 0x010000000000080Bul;
static constexpr u64 TitleId_ArchiveEula                          = 0x010000000000080Cul;
static constexpr u64 TitleId_ArchiveUrlBlackList                  = 0x010000000000080Dul;
static constexpr u64 TitleId_ArchiveTimeZoneBinar                 = 0x010000000000080Eul;
static constexpr u64 TitleId_ArchiveCertStoreCruiser              = 0x010000000000080Ful;
static constexpr u64 TitleId_ArchiveFontNintendoExtension         = 0x0100000000000810ul;
static constexpr u64 TitleId_ArchiveFontStandard                  = 0x0100000000000811ul;
static constexpr u64 TitleId_ArchiveFontKorean                    = 0x0100000000000812ul;
static constexpr u64 TitleId_ArchiveFontChineseTraditional        = 0x0100000000000813ul;
static constexpr u64 TitleId_ArchiveFontChineseSimple             = 0x0100000000000814ul;
static constexpr u64 TitleId_ArchiveFontBfcpx                     = 0x0100000000000815ul;
static constexpr u64 TitleId_ArchiveSystemUpdate                  = 0x0100000000000816ul;

static constexpr u64 TitleId_ArchiveFirmwareDebugSettings         = 0x0100000000000818ul;
static constexpr u64 TitleId_ArchiveBootImagePackage              = 0x0100000000000819ul;
static constexpr u64 TitleId_ArchiveBootImagePackageSafe          = 0x010000000000081Aul;
static constexpr u64 TitleId_ArchiveBootImagePackageExFat         = 0x010000000000081Bul;
static constexpr u64 TitleId_ArchiveBootImagePackageExFatSafe     = 0x010000000000081Cul;
static constexpr u64 TitleId_ArchiveFatalMessage                  = 0x010000000000081Dul;
static constexpr u64 TitleId_ArchiveControllerIcon                = 0x010000000000081Eul;
static constexpr u64 TitleId_ArchivePlatformConfigIcosa           = 0x010000000000081Ful;
static constexpr u64 TitleId_ArchivePlatformConfigCopper          = 0x0100000000000820ul;
static constexpr u64 TitleId_ArchivePlatformConfigHoag            = 0x0100000000000821ul;
static constexpr u64 TitleId_ArchiveControllerFirmware            = 0x0100000000000822ul;
static constexpr u64 TitleId_ArchiveNgWord2                       = 0x0100000000000823ul;
static constexpr u64 TitleId_ArchivePlatformConfigIcosaMariko     = 0x0100000000000824ul;
static constexpr u64 TitleId_ArchiveApplicationBlackList          = 0x0100000000000825ul;
static constexpr u64 TitleId_ArchiveRebootlessSystemUpdateVersion = 0x0100000000000826ul;
static constexpr u64 TitleId_ArchiveContentActionTable            = 0x0100000000000827ul;

static constexpr u64 TitleId_ArchiveEnd                           = 0x0100000000000FFFul;

/* System Applets. */
static constexpr u64 TitleId_AppletStart           = 0x0100000000001000ul;

static constexpr u64 TitleId_AppletQlaunch         = 0x0100000000001000ul;
static constexpr u64 TitleId_AppletAuth            = 0x0100000000001001ul;
static constexpr u64 TitleId_AppletCabinet         = 0x0100000000001002ul;
static constexpr u64 TitleId_AppletController      = 0x0100000000001003ul;
static constexpr u64 TitleId_AppletDataErase       = 0x0100000000001004ul;
static constexpr u64 TitleId_AppletError           = 0x0100000000001005ul;
static constexpr u64 TitleId_AppletNetConnect      = 0x0100000000001006ul;
static constexpr u64 TitleId_AppletPlayerSelect    = 0x0100000000001007ul;
static constexpr u64 TitleId_AppletSwkbd           = 0x0100000000001008ul;
static constexpr u64 TitleId_AppletMiiEdit         = 0x0100000000001009ul;
static constexpr u64 TitleId_AppletWeb             = 0x010000000000100Aul;
static constexpr u64 TitleId_AppletShop            = 0x010000000000100Bul;
static constexpr u64 TitleId_AppletOverlayDisp     = 0x010000000000100Cul;
static constexpr u64 TitleId_AppletPhotoViewer     = 0x010000000000100Dul;
static constexpr u64 TitleId_AppletSet             = 0x010000000000100Eul;
static constexpr u64 TitleId_AppletOfflineWeb      = 0x010000000000100Ful;
static constexpr u64 TitleId_AppletLoginShare      = 0x0100000000001010ul;
static constexpr u64 TitleId_AppletWifiWebAuth     = 0x0100000000001011ul;
static constexpr u64 TitleId_AppletStarter         = 0x0100000000001012ul;
static constexpr u64 TitleId_AppletMyPage          = 0x0100000000001013ul;
static constexpr u64 TitleId_AppletPlayReport      = 0x0100000000001014ul;
static constexpr u64 TitleId_AppletMaintenanceMenu = 0x0100000000001015ul;

static constexpr u64 TitleId_AppletGift            = 0x010000000000101Aul;
static constexpr u64 TitleId_AppletDummyShop       = 0x010000000000101Bul;
static constexpr u64 TitleId_AppletUserMigration   = 0x010000000000101Cul;
static constexpr u64 TitleId_AppletEncounter       = 0x010000000000101Dul;

static constexpr u64 TitleId_AppletStory           = 0x0100000000001020ul;

static constexpr u64 TitleId_AppletEnd             = 0x0100000000001FFFul;

/* Debug Applets. */

/* Debug Modules. */

/* Factory Setup. */

/* Applications. */
static constexpr u64 TitleId_ApplicationStart   = 0x0100000000010000ul;
static constexpr u64 TitleId_ApplicationEnd     = 0x01FFFFFFFFFFFFFFul;

/* Target Tools. */

/* Helper functions. */
static inline bool TitleIdIsSystem(const u64 title_id) {
    return TitleId_SystemStart <= title_id && title_id <= TitleId_SystemEnd;
}

static inline bool TitleIdIsArchive(const u64 title_id) {
    return TitleId_ArchiveStart <= title_id && title_id  <= TitleId_ArchiveEnd;
}

static inline bool TitleIdIsApplet(const u64 title_id) {
    return TitleId_AppletStart <= title_id && title_id  <= TitleId_AppletEnd;
}

static inline bool TitleIdIsApplication(const u64 title_id) {
    return TitleId_ApplicationStart <= title_id && title_id  <= TitleId_ApplicationEnd;
}